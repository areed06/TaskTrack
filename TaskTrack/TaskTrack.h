#ifndef TASKTRACK_H
#define TASKTRACK_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/vscroll.h>
#include <string>
#include <time.h>
#include <thread>
#include "AssignmentDialog.h"
#include "TaskList.h"
#include "AssignmentPanel.h"

// IDs for windows
enum {
    LISTNAME_ID = 0,
    DATETIME_BOX_ID = 1,
    ADDTASK_BTN_ID = 2
};

class TaskTrackApp : public wxApp {
public:
    virtual bool OnInit();

};

class MainFrame : public wxFrame {
private:

    bool eop;
    std::thread time_display_thread;
    TaskList* task_list;
    AssignmentPanel** assignment_panels;

    wxMenuBar* menu_bar;
    wxMenu* file_menu;

    wxBoxSizer* main_sizer;
    wxBoxSizer* V1;
    wxBoxSizer* V2;
    wxBoxSizer* V3;
    wxBoxSizer* V3_top;

    wxScrolledWindow* scrolled;
    
    wxStaticText* listname;
    wxStaticText* datetime;

    wxButton* add_task;

    AssignmentDialog* create_assignment;

    /*
    * Event handlers
    */
    void OnAssignmentEntry(wxCommandEvent& event);
    void OnOpenList(/*wxCommandEvent& event*/);

    wxDECLARE_EVENT_TABLE();

public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~MainFrame();

};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(ADDTASK_BTN_ID, OnAssignmentEntry)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(TaskTrackApp);

#endif