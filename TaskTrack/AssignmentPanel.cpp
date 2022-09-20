#include "AssignmentPanel.h"

AssignmentPanel::AssignmentPanel() : wxPanel() {
	szr = nullptr;
	H1 = nullptr;
	H2 = nullptr;
	H3 = nullptr;
	H4 = nullptr;
	H5 = nullptr;
	H6 = nullptr;
	H7 = nullptr;

	// labels for each data field
	name_label = nullptr;
	description_label = nullptr;
	category_label = nullptr;
	priority_label = nullptr;
	due_date_label = nullptr;
	due_time_label = nullptr;
	progress_label = nullptr;

	// actually stores the assignment info
	name = nullptr;
	description = nullptr;
	category = nullptr;
	priority = nullptr;
	due_date = nullptr;
	due_time = nullptr;
	progress = nullptr;
}

AssignmentPanel::AssignmentPanel(assignment& asmnt, wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_RAISED) {

	// initialize the box sizer
	szr = new wxBoxSizer(wxVERTICAL);
	H1 = new wxBoxSizer(wxHORIZONTAL);
	H2 = new wxBoxSizer(wxHORIZONTAL);
	H3 = new wxBoxSizer(wxHORIZONTAL);
	H4 = new wxBoxSizer(wxHORIZONTAL);
	H5 = new wxBoxSizer(wxHORIZONTAL);
	H6 = new wxBoxSizer(wxHORIZONTAL);
	H7 = new wxBoxSizer(wxHORIZONTAL);

	// initialize labels for data fields
	name_label = new wxStaticText(this, wxID_ANY, wxT("Assignment Name"));
	name_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	description_label = new wxStaticText(this, wxID_ANY, wxT("Description"));
	description_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	category_label = new wxStaticText(this, wxID_ANY, wxT("Category"));
	category_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	priority_label = new wxStaticText(this, wxID_ANY, wxT("Priority"));
	priority_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	due_date_label = new wxStaticText(this, wxID_ANY, wxT("Due Date"));
	due_date_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	due_time_label = new wxStaticText(this, wxID_ANY, wxT("Due Time"));
	due_time_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	progress_label = new wxStaticText(this, wxID_ANY, wxT("Progress"));
	progress_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	// initialize static text objects
	name = new wxStaticText(this, wxID_ANY, asmnt.title, wxDefaultPosition, wxDefaultSize, 0);

	description = new wxStaticText(this, wxID_ANY, asmnt.description, wxDefaultPosition, wxDefaultSize, 0);
	category = new wxStaticText(this, wxID_ANY, asmnt.category, wxDefaultPosition, wxDefaultSize, 0);

	char prio[20];
	switch (asmnt.priority) {
		case 1:
			strncpy(prio, "LOW", 20);
			break;
		case 2:
			strncpy(prio, "MEDIUM", 20);
			break;
		case 3:
			strncpy(prio, "HIGH", 20);
			break;
		default:
			strncpy(prio, "NO_PRIORITY", 20);
			break;
	}
	priority = new wxStaticText(this, wxID_ANY, prio, wxDefaultPosition, wxDefaultSize, 0);

	char due_date_tmp[11];
	sprintf(due_date_tmp, "%02d-%02d-%04d", asmnt.due_month, asmnt.due_day, asmnt.due_year);
	due_date = new wxStaticText(this, wxID_ANY, due_date_tmp, wxDefaultPosition, wxDefaultSize, 0);

	char due_time_tmp[6];
	sprintf(due_time_tmp, "%02d:%02d", asmnt.due_hour, asmnt.due_min);
	due_time = new wxStaticText(this, wxID_ANY, due_time_tmp, wxDefaultPosition, wxDefaultSize, 0);

	progress = new wxStaticText(this, wxID_ANY, wxString::Format("%i%%", asmnt.progress), wxDefaultPosition, wxDefaultSize, 0);

	// add items to sizer
	H1->Add(name_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H1->Add(name, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H2->Add(description_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H2->Add(description, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	
	H3->Add(category_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H3->Add(category, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H4->Add(priority_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H4->Add(priority, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H5->Add(due_date_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H5->Add(due_date, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H6->Add(due_time_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H6->Add(due_time, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H7->Add(progress_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H7->Add(progress, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	szr->Add(H1, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H2, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H3, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H4, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H5, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H6, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H7, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

	SetSizer(szr);
	szr->Fit(this);
	szr->SetSizeHints(this);
}

AssignmentPanel::AssignmentPanel(const AssignmentPanel& source) {

	// initialize the box sizer
	szr = new wxBoxSizer(wxVERTICAL);
	H1 = new wxBoxSizer(wxHORIZONTAL);
	H2 = new wxBoxSizer(wxHORIZONTAL);
	H3 = new wxBoxSizer(wxHORIZONTAL);
	H4 = new wxBoxSizer(wxHORIZONTAL);
	H5 = new wxBoxSizer(wxHORIZONTAL);
	H6 = new wxBoxSizer(wxHORIZONTAL);
	H7 = new wxBoxSizer(wxHORIZONTAL);

	// initialize labels for data fields
	name_label = new wxStaticText(this, wxID_ANY, wxT("Assignment Name"));
	name_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	description_label = new wxStaticText(this, wxID_ANY, wxT("Description"));
	description_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	category_label = new wxStaticText(this, wxID_ANY, wxT("Category"));
	category_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	priority_label = new wxStaticText(this, wxID_ANY, wxT("Priority"));
	priority_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	due_date_label = new wxStaticText(this, wxID_ANY, wxT("Due Date"));
	due_date_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	due_time_label = new wxStaticText(this, wxID_ANY, wxT("Due Time"));
	due_time_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	progress_label = new wxStaticText(this, wxID_ANY, wxT("Progress"));
	progress_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	// initialize static text objects
	name = new wxStaticText(this, wxID_ANY, source.name->GetLabel(), wxDefaultPosition, wxDefaultSize, 0);

	description = new wxStaticText(this, wxID_ANY, source.description->GetLabel(), wxDefaultPosition, wxDefaultSize, 0);
	category = new wxStaticText(this, wxID_ANY, source.category->GetLabel(), wxDefaultPosition, wxDefaultSize, 0);

	char prio[20];
	int p = wxAtoi(source.priority->GetLabel());
	switch (p) {
	case 1:
		strncpy(prio, "LOW", 20);
		break;
	case 2:
		strncpy(prio, "MEDIUM", 20);
		break;
	case 3:
		strncpy(prio, "HIGH", 20);
		break;
	default:
		strncpy(prio, "NO_PRIORITY", 20);
		break;
	}
	priority = new wxStaticText(this, wxID_ANY, prio, wxDefaultPosition, wxDefaultSize, 0);

	char due_date_tmp[11];
	int m, d, y;
	sscanf_s(source.due_date->GetLabel().mb_str(), "%02d-%02d-%04d", &m, &d, &y);
	sprintf(due_date_tmp, "%02d-%02d-%04d", m, d, y);
	due_date = new wxStaticText(this, wxID_ANY, due_date_tmp, wxDefaultPosition, wxDefaultSize, 0);

	char due_time_tmp[6];
	int h, min;
	sscanf_s(source.due_time->GetLabel().mb_str(), "%02d:%02d", &h, &min);
	sprintf(due_time_tmp, "%02d:%02d", h, min);
	due_time = new wxStaticText(this, wxID_ANY, due_time_tmp, wxDefaultPosition, wxDefaultSize, 0);

	progress = new wxStaticText(this, wxID_ANY, wxString::Format("%i%%", wxAtoi(source.progress->GetLabel())), wxDefaultPosition, wxDefaultSize, 0);

	// add items to sizer
	H1->Add(name_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H1->Add(name, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H2->Add(description_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H2->Add(description, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H3->Add(category_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H3->Add(category, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H4->Add(priority_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H4->Add(priority, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H5->Add(due_date_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H5->Add(due_date, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H6->Add(due_time_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H6->Add(due_time, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H7->Add(progress_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H7->Add(progress, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	szr->Add(H1, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H2, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H3, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H4, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H5, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H6, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H7, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

	SetSizer(szr);
	szr->Fit(this);
	szr->SetSizeHints(this);

}

AssignmentPanel::~AssignmentPanel() {

	// children of sizer are automatically deleted when it is deleted
	// main sizer will be destroyed when AssignmentPanel is deleted

	delete name;
	delete name_label;

	delete description;
	delete description_label;

	delete category;
	delete category_label;

	delete due_date;
	delete due_date_label;

	delete due_time;
	delete due_time_label;

	delete progress;
	delete progress_label;
}

AssignmentPanel& AssignmentPanel::operator=(const AssignmentPanel& source) {

	if (this == &source) {
		return *this;
	}

	// Need to first delete the existing members (to avoid memory leaks)

	delete szr;
	delete H1;
	delete H2;
	delete H3;
	delete H4;
	delete H5;
	delete H6;
	delete H7;

	delete name_label;
	delete description_label;
	delete category_label;
	delete priority_label;
	delete due_date_label;
	delete due_time_label;
	delete progress_label;

	delete name;
	delete description;
	delete category;
	delete priority;
	delete due_date;
	delete due_time;
	delete progress;

	szr = new wxBoxSizer(wxVERTICAL);
	H1 = new wxBoxSizer(wxHORIZONTAL);
	H2 = new wxBoxSizer(wxHORIZONTAL);
	H3 = new wxBoxSizer(wxHORIZONTAL);
	H4 = new wxBoxSizer(wxHORIZONTAL);
	H5 = new wxBoxSizer(wxHORIZONTAL);
	H6 = new wxBoxSizer(wxHORIZONTAL);
	H7 = new wxBoxSizer(wxHORIZONTAL);

	// initialize labels for data fields
	name_label = new wxStaticText(this, wxID_ANY, wxT("Assignment Name"));
	name_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	description_label = new wxStaticText(this, wxID_ANY, wxT("Description"));
	description_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	category_label = new wxStaticText(this, wxID_ANY, wxT("Category"));
	category_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	priority_label = new wxStaticText(this, wxID_ANY, wxT("Priority"));
	priority_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	due_date_label = new wxStaticText(this, wxID_ANY, wxT("Due Date"));
	due_date_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	due_time_label = new wxStaticText(this, wxID_ANY, wxT("Due Time"));
	due_time_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	progress_label = new wxStaticText(this, wxID_ANY, wxT("Progress"));
	progress_label->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	// initialize static text objects
	name = new wxStaticText(this, wxID_ANY, source.name->GetLabel(), wxDefaultPosition, wxDefaultSize, 0);

	description = new wxStaticText(this, wxID_ANY, source.description->GetLabel(), wxDefaultPosition, wxDefaultSize, 0);
	category = new wxStaticText(this, wxID_ANY, source.category->GetLabel(), wxDefaultPosition, wxDefaultSize, 0);

	char prio[20];
	int p = wxAtoi(source.priority->GetLabel());
	switch (p) {
	case 1:
		strncpy(prio, "LOW", 20);
		break;
	case 2:
		strncpy(prio, "MEDIUM", 20);
		break;
	case 3:
		strncpy(prio, "HIGH", 20);
		break;
	default:
		strncpy(prio, "NO_PRIORITY", 20);
		break;
	}
	priority = new wxStaticText(this, wxID_ANY, prio, wxDefaultPosition, wxDefaultSize, 0);

	char due_date_tmp[11];
	int m, d, y;
	sscanf_s(source.due_date->GetLabel().mb_str(), "%02d-%02d-%04d", &m, &d, &y);
	sprintf(due_date_tmp, "%02d-%02d-%04d", m, d, y);
	due_date = new wxStaticText(this, wxID_ANY, due_date_tmp, wxDefaultPosition, wxDefaultSize, 0);

	char due_time_tmp[6];
	int h, min;
	sscanf_s(source.due_time->GetLabel().mb_str(), "%02d:%02d", &h, &min);
	sprintf(due_time_tmp, "%02d:%02d", h, min);
	due_time = new wxStaticText(this, wxID_ANY, due_time_tmp, wxDefaultPosition, wxDefaultSize, 0);

	progress = new wxStaticText(this, wxID_ANY, wxString::Format("%i%%", wxAtoi(source.progress->GetLabel())), wxDefaultPosition, wxDefaultSize, 0);

	// add items to sizer
	H1->Add(name_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H1->Add(name, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H2->Add(description_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H2->Add(description, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H3->Add(category_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H3->Add(category, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H4->Add(priority_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H4->Add(priority, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H5->Add(due_date_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H5->Add(due_date, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H6->Add(due_time_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H6->Add(due_time, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	H7->Add(progress_label, 0, wxALIGN_LEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 20);
	H7->Add(progress, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	szr->Add(H1, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H2, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H3, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H4, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H5, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H6, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
	szr->Add(H7, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

	SetSizer(szr);
	szr->Fit(this);
	szr->SetSizeHints(this);

	return *this;
}