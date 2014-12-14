// ----------------------------------------------------------------------
// equipAlignWindow.h
//     Copyright © Brad Triebwasser 2010
/* Description:
	Used for aligning equipment
*/
// ------------------------------------------------------------------------


#include <wx/wx.h>
#include <equipmentData.h>
#include "equipAlignChoosePart.h"

#ifndef _H_EQUIPALIGNWINDOW
#define _H_EQUIPALIGNWINDOW
class equipAlignRenderer;
enum WidgetIDS {
	ID_BTN_ALIGNEQUIPMENT,
	ID_BTN_SAVE,
	ID_BTNALIGNFACIALHAIR,
	ID_BTNALIGNHAIR,
	ID_BTNALIGNEYES,
	ID_BTNALIGNMOUTH,
	ID_BTNALIGNEAR
};
class equipAlignWindow : public wxFrame {
public:
	equipAlignWindow();
	~equipAlignWindow();

private:

	wxFlexGridSizer*			mainSizer;

	wxStaticText*		staticText_selectEquipment;
	wxTextCtrl*			textBox_equipmentID;
	wxButton*			button_alignEquipment;


	wxStaticText*		staticText_selectFacialHair;
	wxTextCtrl*			textBox_facialHairID;
	wxButton*			button_alignFacialHair;

	wxStaticText*		staticText_selectHair;
	wxTextCtrl*			textBox_hairID;
	wxButton*			button_alignHair;

	wxStaticText*		staticText_selectEyes;
	wxTextCtrl*			textBox_eyesID;
	wxButton*			button_alignEyes;

	wxStaticText*		staticText_selectMouth;
	wxTextCtrl*			textBox_mouthID;
	wxButton*			button_alignMouth;

	wxStaticText*		staticText_selectEar;
	wxTextCtrl*			textBox_earID;
	wxButton*			button_alignEar;

	wxStaticText*		staticText_raceID;
	wxTextCtrl*			textBox_raceSelect;


	void destoyEquipmentSelectionControls();

public:
	void createAlignmentControls(std::string bodyPartImagePath, std::string bodyPartDataPath, std::string imageName, std::string dataPath);
	void createAlignmentControls(std::pair<std::string,std::string> bodyPath, std::string imageName, std::string dataPath);

	std::pair<std::string,std::string>getBodyPartPath(int skinID, int skinColor, std::string partName);
	std::pair<std::string,std::string> getBodyPartPath(int skinID, int skinColor, int equipID);

	wxBitmap*			bodyPartBitmap;
	wxPoint*			bodyPartPosition;
	wxPoint*			bodyPartSpriteOrigin;
	wxBitmap*			equipmentBitmap;
	wxPoint*			equipmentPosition;
	wxPoint*			equipmentSpriteOrigin;
	std::string			fullImagePath;
	std::string			fullDataPath;
	wxBoxSizer*			alignSizer;
	wxButton*			saveButton;
	equipAlignRenderer* alignmentRenderer;

private:
	void alignEquipmentButton(wxCommandEvent &event);
	void alignfacialHairButton(wxCommandEvent &event);
	void alignHairButton(wxCommandEvent &event);
	void alignEyesButton(wxCommandEvent &event);
	void alignMouthButton(wxCommandEvent &event);
	void alignEarButton(wxCommandEvent &event);
	void alignSaveButton(wxCommandEvent &event);
	void keyDown(wxKeyEvent &event);
    DECLARE_EVENT_TABLE()

};

#endif 