#ifndef ASSIGNMENT_PANEL_H
#define ASSIGNMENT_PANEL_H

#include <wx/wx.h>
#include "assignment.h"

class AssignmentPanel : public wxPanel {
private:
	wxBoxSizer* szr;
	wxBoxSizer* H1;
	wxBoxSizer* H2;
	wxBoxSizer* H3;
	wxBoxSizer* H4;
	wxBoxSizer* H5;
	wxBoxSizer* H6;
	wxBoxSizer* H7;

	// labels for each data field
	wxStaticText* name_label;
	wxStaticText* description_label;
	wxStaticText* category_label;
	wxStaticText* priority_label;
	wxStaticText* due_date_label;
	wxStaticText* due_time_label;
	wxStaticText* progress_label;

	// actually stores the assignment info
	wxStaticText* name;
	wxStaticText* description;
	wxStaticText* category;
	wxStaticText* priority;
	wxStaticText* due_date;
	wxStaticText* due_time;
	wxStaticText* progress;

public:
	AssignmentPanel();												// default constructor
	AssignmentPanel(const AssignmentPanel& source);					// copy constructor
	AssignmentPanel(assignment& asmnt, wxWindow* parent);
	~AssignmentPanel();
	AssignmentPanel& operator=(const AssignmentPanel& source);
};

#endif