#include "applicationFrame.h"
#include "equipAlignWindow.h"

BEGIN_EVENT_TABLE(applicationFrame, wxFrame)
    EVT_MENU(ID_QUIT,  applicationFrame::OnQuit)
	EVT_MENU(ID_ALIGNEQUIPMENT,  applicationFrame::alignEquipment)
END_EVENT_TABLE()


applicationFrame::applicationFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame(NULL, -1, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->AppendSeparator();
    menuFile->Append(ID_QUIT, _("E&xit") );

	wxMenu *menuTools = new wxMenu;
	menuTools->Append(ID_ALIGNEQUIPMENT,_("Equipment Aligner"));

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, _("&File") );
	menuBar->Append(menuTools, _("Tools"));

    SetMenuBar( menuBar );

    CreateStatusBar();
    SetStatusText( _("Grand Tale Developer Toolset.") );

	wxNotebook* pageManager = new wxNotebook(this,ID_NOTEBOOK); //Create the notebook






}


void applicationFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void applicationFrame::alignEquipment(wxCommandEvent &event) {
	equipAlignWindow* alignWindow = new equipAlignWindow();
	alignWindow->Show();
}