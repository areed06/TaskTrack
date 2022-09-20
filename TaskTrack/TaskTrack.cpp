#include "TaskTrack.h"

/* get_date_time:
* -- Returns the date & time formatted as desired
* @arg now -> current date+time
* @ret buf -> string with formatted date and time
*/
std::string get_date_time(time_t now) {
    struct tm tstruct;
    char buf[80];

    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%m-%d-%Y  %X", &tstruct);

    return buf;
}

/* update_time:
* -- A thread will be dedicated to updating the displayed time every second
* @arg txt -> pointer to the wxStaticText object
* @ret void
*/
void update_time(wxStaticText* txt, const bool* end_of_program) {

    time_t t0 = time(0);
    time_t t1 = t0;

    while (!(*end_of_program)) {

        t1 = time(0);
        if (t1 - t0 > 0) {
            txt->SetLabel(wxString(get_date_time(t1)));
            t0 = t1;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return;
}

/* TaskTrackApp::OnInit
* -- Instantiates the main GUI window and shows it 
*/
bool TaskTrackApp::OnInit() {
    MainFrame* frame = new MainFrame("TaskTrack", wxPoint(50, 50), wxDefaultSize);
    frame->Show(true);

    return true;
}

/* MainFrame:
* -- Constructor which instantiates all GUI controls and elements
* -- Everything contained in sizers are added in a hierarchy of sizers
*/
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size) {

    // Initializing member variables
    eop = 0;

    // Configuring the frame
    SetBackgroundColour(wxColour(255, 255, 230, 0));
    SetMinSize(wxSize(600, 450));

    // Sizers which can contain different controls
    main_sizer = new wxBoxSizer(wxVERTICAL);
    V1 = new wxBoxSizer(wxHORIZONTAL);
    V2 = new wxBoxSizer(wxHORIZONTAL);
    V3 = new wxBoxSizer(wxVERTICAL);

    /*
    * Creating controls and displays and their formatting
    */

    // creating menu bar
    file_menu = new wxMenu();
    file_menu->Append(wxID_OPEN, _T("&Open"));
    file_menu->Append(wxID_SAVE, _T("&Save"));
    file_menu->Append(wxID_CLOSE, _T("&Close"));
    file_menu->Append(wxID_PREFERENCES, _T("&Preferences"));
    file_menu->Append(wxID_EXIT, _T("&Quit"));

    menu_bar = new wxMenuBar();
    menu_bar->Append(file_menu, _T("&File"));
    SetMenuBar(menu_bar);

    // stores the name of the current list being examined
    listname = new wxStaticText(this, LISTNAME_ID, wxString("List Name"), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_LEFT);
    listname->SetFont(wxFont(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    // displays current date
    datetime = new wxStaticText(this, DATETIME_BOX_ID, wxString(get_date_time(time(0))), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE | wxALIGN_RIGHT);
    datetime->SetFont(wxFont(18, wxFONTFAMILY_SWISS, wxFONTSTYLE_SLANT, wxFONTWEIGHT_BOLD));

    add_task = new wxButton(this, ADDTASK_BTN_ID, wxString("Add Task"), wxDefaultPosition, wxDefaultSize);

    /*
    * Adding controls to the window
    * Keeping this code here makes it easier to see the hierarchy of the GUI
    */
    SetSizer(main_sizer);

    V1->Add(listname, 1, wxEXPAND | wxALL, 20);
    V1->Add(datetime, 1, wxEXPAND | wxALL, 20);

    V2->Add(add_task, 0, wxALIGN_TOP | wxLEFT | wxRIGHT, 20);

    OnOpenList();

    scrolled->SetSizer(V3);
    scrolled->EnableScrolling(0, 1);
    V3_top->Add(scrolled, 1, wxEXPAND | wxALL, 20);

    main_sizer->Add(V1, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(V2, 0, wxALIGN_TOP | wxLEFT | wxRIGHT, 10);
    main_sizer->Add(V3_top, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    main_sizer->Fit(this);
    //main_sizer->SetSizeHints(this);       // this line sets sizer to minimum size (can't make it smaller)

    // Updates the current time every second
    time_display_thread = std::thread(update_time, datetime, &eop);
}

/* ~MainFrame:
* -- Destructor for main GUI window
* -- eop signal triggers any separate threads to finish executing so they can be joined
*/
MainFrame::~MainFrame() {

    // trigger the time keeper to end
    eop = 1;
    time_display_thread.join();

    /* If create_assignment is not deleted in the destructor for MainFrame,
     * the program will continue running */
    delete create_assignment;

}

/* OnAssignmentEntry:
* -- This function will create and show a dialog to create a new assignment
* @arg event -> wxCommandEvent which prompts execution of the function
*/
void MainFrame::OnAssignmentEntry(wxCommandEvent& event) {
    create_assignment = new AssignmentDialog(wxID_ANY, (wxString&)wxString("Create Assignment"), task_list);
    int rtn = create_assignment->ShowModal();     // ShowModal() returns int which is ignored here

    if (rtn == ttNEW_ASSIGNMENT) {
        int cnt = task_list->assignment_count();
        assignment_panels[cnt] = new AssignmentPanel(task_list->assignments[cnt], scrolled);
        V3->Add(assignment_panels[cnt], 0, wxEXPAND | wxRIGHT | wxBOTTOM, 20);
    }

    return;
}

void MainFrame::OnOpenList(/*wxCommand& event*/) {

    V3->Clear();

    char fname[] = "C:\\Users\\alree\\Documents\\Personal\\Software Projects\\TaskTrackFileSystem\\tasklist1.csv";
    task_list = new TaskList();
    task_list->loadList(fname);

    V3_top = new wxBoxSizer(wxVERTICAL);
    scrolled = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500), wxVSCROLL);
    scrolled->SetScrollRate(0, 5);

    listname->SetLabel(task_list->name());

    int num_asmnt = task_list->assignment_count();
    assignment_panels = new AssignmentPanel*[num_asmnt + 10];
    for (int x = 0; x < num_asmnt; x++) {
        assignment_panels[x] = new AssignmentPanel(task_list->assignments[x], scrolled);
        V3->Add(assignment_panels[x], 0, wxEXPAND | wxRIGHT | wxBOTTOM, 20);
    }

    return;
}