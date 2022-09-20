#ifndef ASSIGNMENTDIALOG_H
#define ASSIGNMENTDIALOG_H

#include "wx/wx.h"
#include "wx/calctrl.h"
#include "wx/timectrl.h"
#include "assignment.h"
#include "TaskList.h"
#include <vector>

#define ttNEW_ASSIGNMENT 1

enum {
	ID_SAVE_BTN = 10,
	ID_CANCEL_BTN = 11
};

class AssignmentDialog : public wxDialog {
private:

	/*
	* Private Members
	*/
	TaskList* list;

	/*
	* Sizers
	*/
	wxBoxSizer* main_sizer;
	wxBoxSizer* H1;
	wxBoxSizer* H2;

	/* 
	* Controls for data fields for assignment entries
	*/
	wxChoice* priority;				// priority level selection
	wxTextCtrl* description;		// description of the event
	wxCalendarCtrl* due_date;		// selection of due date
	wxTimePickerCtrl* due_time;		// selection of due time
	wxChoice* category;				// selection of course/subject/category

	/*
	* Other controls for the dialog
	*/
	wxButton* save;
	wxButton* cancel;

	/*
	* Event handlers
	*/
	void OnSaveAssignment(wxCommandEvent& evt);
	void OnCancel(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

public:
	AssignmentDialog(wxWindowID ID, wxString& title, TaskList* tl);
	~AssignmentDialog();

};

#endif