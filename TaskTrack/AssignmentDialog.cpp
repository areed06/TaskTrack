/* NOTES
 * Need to make selectable options loaded from file or settings 
 * 
 */

#include "AssignmentDialog.h"

AssignmentDialog::AssignmentDialog(wxWindowID ID, wxString& title, TaskList* tl) : wxDialog(NULL, ID, title, wxDefaultPosition, wxDefaultSize) {

	list = tl;

	main_sizer = new wxBoxSizer(wxVERTICAL);
	H1 = new wxBoxSizer(wxHORIZONTAL);
	H2 = new wxBoxSizer(wxHORIZONTAL);

	std::vector<wxString> priority_levels{ wxT("LOW"), wxT("MEDIUM"), wxT("HIGH") };
	wxArrayString priorities;
	std::for_each(priority_levels.begin(), priority_levels.end(), [&](const wxString& s) {priorities.Add(s); });
	priority = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, priorities);
	priority->SetLabel(wxString("Priority Level"));

	description = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	description->SetLabel(wxString("Task Description"));

	due_date = new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SUNDAY_FIRST);
	due_date->SetLabel(wxString("Due Date"));

	due_time = new wxTimePickerCtrl(this, wxID_ANY);
	due_time->SetLabel(wxString("Due Time"));

	std::vector<wxString> category_options{ wxT("EECE2322"), wxT("EECE2323"), wxT("EECE3410") };
	wxArrayString categories_list;
	std::for_each(category_options.begin(), category_options.end(), [&](const wxString& s) {categories_list.Add(s); });
	category = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, categories_list);
	category->SetLabel(wxString("Category"));

	save = new wxButton(this, ID_SAVE_BTN, wxString("Save"), wxDefaultPosition, wxDefaultSize);
	cancel = new wxButton(this, ID_CANCEL_BTN, wxString("Cancel"), wxDefaultPosition, wxDefaultSize);

	H1->Add(priority, 0, wxRIGHT, 10);
	H1->Add(description, 1, wxEXPAND | wxRIGHT, 10);
	H1->Add(category, 0, wxRIGHT, 10);

	H2->Add(save, 0, wxALL, 10);
	H2->Add(cancel, 0, wxALL, 10);

	main_sizer->Add(H1, 0, wxEXPAND | wxALL, 10);
	main_sizer->Add(due_date, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxALIGN_CENTER, 10);
	main_sizer->Add(due_time, 0, wxLEFT | wxRIGHT | wxALIGN_CENTER, 10);
	main_sizer->Add(H2, 0, wxALL | wxBOTTOM | wxALIGN_RIGHT, 10);

	SetSizerAndFit(main_sizer);
}

AssignmentDialog::~AssignmentDialog() {
	delete due_date;
	delete category;
	delete description;
	delete priority;
}

void AssignmentDialog::OnSaveAssignment(wxCommandEvent& evt) {
	
	// handling no selected
	int cat_sel = category->GetSelection();
	if (cat_sel == wxNOT_FOUND) {
		cat_sel = 0;
	}

	int h, m, s;
	due_time->GetTime(&h, &m, &s);
	assignment tmp = {	_strdup("Name"),
						_strdup(description->GetLineText(0).mb_str()),
						_strdup(category->GetString(cat_sel).mb_str()),
						2,
						due_date->GetDate().GetMonth(),
						due_date->GetDate().GetDay(),
						due_date->GetDate().GetYear(),
						h,
						m,
						0
					  };

	list->add(tmp);

	delete tmp.title;
	delete tmp.description;
	delete tmp.category;

	AssignmentDialog::EndModal(ttNEW_ASSIGNMENT);
}

void AssignmentDialog::OnCancel(wxCommandEvent& evt) {
	AssignmentDialog::EndModal(0);
}

wxBEGIN_EVENT_TABLE(AssignmentDialog, wxDialog)
EVT_BUTTON(ID_SAVE_BTN, AssignmentDialog::OnSaveAssignment)
EVT_BUTTON(ID_CANCEL_BTN, AssignmentDialog::OnCancel)
wxEND_EVENT_TABLE()