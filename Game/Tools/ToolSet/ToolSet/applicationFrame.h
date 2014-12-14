#include <wx/wx.h>
#include <wx/notebook.h>

#ifndef _H_APPFRAME
#define _H_APPFRAME

enum {
	ID_QUIT,
	ID_ALIGNEQUIPMENT,
	ID_NOTEBOOK,
	ID_EQUIPLIST
};
class equipmentManagerPanel;
class applicationFrame : public wxFrame
{
public:
    applicationFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void OnQuit(wxCommandEvent& event);
	void alignEquipment(wxCommandEvent &event);
    DECLARE_EVENT_TABLE()

	wxNotebook* pageManager;
};

#endif