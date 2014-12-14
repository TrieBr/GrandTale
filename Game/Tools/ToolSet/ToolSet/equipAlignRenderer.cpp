#include "equipAlignRenderer.h"

BEGIN_EVENT_TABLE(equipAlignRenderer, wxPanel)
    EVT_PAINT(equipAlignRenderer::onPaint)
	
END_EVENT_TABLE()

 


equipAlignRenderer::equipAlignRenderer(equipAlignWindow* parentAlignWindow, wxWindow *parent)
	: wxPanel (parent,0,0,128,128)
{
	this ->parentAlignWindow = parentAlignWindow;
	xOrigin =(this->GetSize().GetWidth()/2);
	yOrigin =(this->GetSize().GetHeight()/2);
}


void equipAlignRenderer::onPaint(wxPaintEvent& event) {
	wxPaintDC draw(this);
		draw.SetBackground(wxBrush(wxColor("gray")));
			draw.Clear();
		
		draw.DrawBitmap(*parentAlignWindow->bodyPartBitmap,wxPoint(xOrigin-parentAlignWindow->bodyPartSpriteOrigin->x,yOrigin-parentAlignWindow->bodyPartSpriteOrigin->y));
		draw.DrawBitmap(*parentAlignWindow->equipmentBitmap,wxPoint(xOrigin+parentAlignWindow->equipmentPosition->x-parentAlignWindow->equipmentSpriteOrigin->x,yOrigin+parentAlignWindow->equipmentPosition->y-parentAlignWindow->equipmentSpriteOrigin->y));

}

