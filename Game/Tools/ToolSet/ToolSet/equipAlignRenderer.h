
#include <wx/wx.h>
#include "equipAlignWindow.h"



class equipAlignRenderer : public wxPanel {
public:
	equipAlignRenderer(equipAlignWindow* parentAlignWindow, wxWindow *parent);

	equipAlignWindow* parentAlignWindow;

	void onPaint(wxPaintEvent& event);
	int xOrigin;
	int yOrigin;
    DECLARE_EVENT_TABLE()
};