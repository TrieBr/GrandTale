
#include "equipAlignWindow.h"
#include <sstream>
#include <wx/wfstream.h>
#include <fstream>
#include "mainApplication.h"
#include "equipAlignRenderer.h"
BEGIN_EVENT_TABLE(equipAlignWindow, wxFrame)
	EVT_BUTTON(ID_BTN_ALIGNEQUIPMENT,  equipAlignWindow::alignEquipmentButton)
	EVT_BUTTON(ID_BTNALIGNFACIALHAIR,  equipAlignWindow::alignfacialHairButton)
	EVT_BUTTON(ID_BTNALIGNHAIR,  equipAlignWindow::alignHairButton)
	EVT_BUTTON(ID_BTNALIGNEYES,  equipAlignWindow::alignEyesButton)
	EVT_BUTTON(ID_BTNALIGNMOUTH,  equipAlignWindow::alignMouthButton)
	EVT_BUTTON(ID_BTNALIGNEAR,  equipAlignWindow::alignEarButton)
	EVT_BUTTON(ID_BTN_SAVE,  equipAlignWindow::alignSaveButton)
	EVT_KEY_DOWN(equipAlignWindow::keyDown)
END_EVENT_TABLE()

equipAlignWindow::equipAlignWindow()
	: wxFrame(NULL,-1,_("Equipment Alignment"))
{
	this->SetBackgroundColour(wxColour(wxNullColour));

	mainSizer =						new wxFlexGridSizer(4,5,5);


	staticText_selectEquipment =	new wxStaticText(this,-1,_("Enter the ID of a peice of equipment:"));
	textBox_equipmentID =			new wxTextCtrl(this,-1,wxEmptyString,wxPoint(5,5));
	button_alignEquipment=			new wxButton(this,ID_BTN_ALIGNEQUIPMENT,_("Align Equipment"));

	mainSizer->Add(staticText_selectEquipment,4,0,8);
	mainSizer->Add(textBox_equipmentID,1,0,8);
	mainSizer->Add(button_alignEquipment,1,0,8);
	mainSizer->AddStretchSpacer(1);

	staticText_selectFacialHair =	new wxStaticText(this,-1,_("Enter facial hair ID:"));
	textBox_facialHairID  =			new wxTextCtrl(this,-1,wxEmptyString,wxPoint(5,5));
	button_alignFacialHair =		new wxButton(this,ID_BTNALIGNFACIALHAIR,_("Align Facial Hair"));
	
	mainSizer->Add(staticText_selectFacialHair,4,0,8);
	mainSizer->Add(textBox_facialHairID,1,0,8);
	mainSizer->Add(button_alignFacialHair,1,0,8);
	mainSizer->AddStretchSpacer(1);

	staticText_selectHair =			new wxStaticText(this,-1,_("Enter hair ID:"));
	textBox_hairID=					new wxTextCtrl(this,-1,wxEmptyString,wxPoint(5,5));
	button_alignHair=				new wxButton(this,ID_BTNALIGNHAIR,_("Align Hair"));

	mainSizer->Add(staticText_selectHair,4,0,8);
	mainSizer->Add(textBox_hairID,1,0,8);
	mainSizer->Add(button_alignHair,1,0,8);
	mainSizer->AddStretchSpacer(1);

	staticText_selectEyes=			new wxStaticText(this,-1,_("Enter eyes ID:"));
	textBox_eyesID=					new wxTextCtrl(this,-1,wxEmptyString,wxPoint(5,5));
	button_alignEyes=				new wxButton(this,ID_BTNALIGNEYES,_("Align Eyes"));

	mainSizer->Add(staticText_selectEyes,4,0,8);
	mainSizer->Add(textBox_eyesID,1,0,8);
	mainSizer->Add(button_alignEyes,1,0,8);
	mainSizer->AddStretchSpacer(1);


	staticText_selectMouth=			new wxStaticText(this,-1,_("Enter mouth ID:"));
	textBox_mouthID=					new wxTextCtrl(this,-1,wxEmptyString,wxPoint(5,5));
	button_alignMouth=				new wxButton(this,ID_BTNALIGNMOUTH,_("Align Mouth"));

	mainSizer->Add(staticText_selectMouth,4,0,8);
	mainSizer->Add(textBox_mouthID,1,0,8);
	mainSizer->Add(button_alignMouth,1,0,8);
	mainSizer->AddStretchSpacer(1);


	staticText_selectEar=			new wxStaticText(this,-1,_("Enter Ear (race) ID:"));
	textBox_earID=					new wxTextCtrl(this,-1,wxEmptyString,wxPoint(5,5));
	button_alignEar=				new wxButton(this,ID_BTNALIGNEAR,_("Align Ear"));

	mainSizer->Add(staticText_selectEar,4,0,8);
	mainSizer->Add(textBox_earID,1,0,8);
	mainSizer->Add(button_alignEar,1,0,8);
	mainSizer->AddStretchSpacer(1);


	staticText_raceID =			new wxStaticText(this,-1,_("Enter race to align with:"));
	textBox_raceSelect=			new wxTextCtrl(this,-1,_("0"),wxPoint(5,5));

	mainSizer->Add(staticText_raceID,4,0,8);
	mainSizer->Add(textBox_raceSelect,1,0,8);
	mainSizer->AddStretchSpacer(1);
	mainSizer->AddStretchSpacer(1);

	this->SetSizer(mainSizer);
	this->Layout();
}


equipAlignWindow::~equipAlignWindow() {


}

void equipAlignWindow::destoyEquipmentSelectionControls() {
	delete staticText_selectEquipment;
	delete textBox_equipmentID;
	delete button_alignEquipment;

	delete staticText_selectFacialHair;
	delete textBox_facialHairID;
	delete button_alignFacialHair;

	delete staticText_selectHair;
	delete textBox_hairID;
	delete button_alignHair;

	delete staticText_selectEyes;
	delete textBox_eyesID;
	delete button_alignEyes;

	delete staticText_selectMouth;
	delete textBox_mouthID;
	delete button_alignMouth;

	delete staticText_selectEar;
	delete textBox_earID;
	delete button_alignEar;

	delete staticText_raceID;
	delete textBox_raceSelect;
	this->SetSizer(NULL);
}

void equipAlignWindow::alignEarButton(wxCommandEvent &event) {
	int					raceID;
	std::stringstream	IDParser;
	std::string			imageName;
	std::string			dataName;
	std::stringstream	nameParser;

	IDParser << textBox_earID->GetValue().c_str(); //Read the string from the text box into the stringstream
	IDParser >> raceID; //Extract the value from the string stream and cast it to an integer

	destoyEquipmentSelectionControls();

	nameParser << "race\\" << raceID << "\\skinColor\\0\\" << "Ear.png";
	imageName = nameParser.str();
	nameParser.str("");
	nameParser << "race\\" << raceID << "\\" << "Ear.raw";
	dataName = nameParser.str();
	createAlignmentControls(getBodyPartPath(raceID,0,"Head"),imageName,dataName);
}

void equipAlignWindow::alignEyesButton(wxCommandEvent &event) {
	int					faceID;
	std::stringstream	IDParser;
	std::string			imageName;
	std::string			dataName;
	std::stringstream	nameParser;
	int					raceID;

	IDParser << textBox_eyesID->GetValue().c_str(); //Read the string from the text box into the stringstream
	IDParser >> faceID; //Extract the value from the string stream and cast it to an integer

	std::stringstream	 IDParser2;
	IDParser2 << textBox_raceSelect->GetValue().c_str(); //Get the race to align with
	IDParser2 >> raceID;
	

	destoyEquipmentSelectionControls();

	nameParser << "eyes\\" << faceID  << ".png";
	imageName = nameParser.str();
	nameParser.str("");
	nameParser << "eyes\\" << faceID << ".raw";
	dataName = nameParser.str();
	createAlignmentControls(getBodyPartPath(raceID,0,"Head"),imageName,dataName);
}

void equipAlignWindow::alignMouthButton(wxCommandEvent &event) {
	int					mouthID;
	std::stringstream	IDParser;
	std::string			imageName;
	std::string			dataName;
	std::stringstream	nameParser;
	int					raceID;

	IDParser << textBox_mouthID->GetValue().c_str(); //Read the string from the text box into the stringstream
	IDParser >> mouthID; //Extract the value from the string stream and cast it to an integer

	std::stringstream	 IDParser2;
	IDParser2 << textBox_raceSelect->GetValue().c_str(); //Get the race to align with
	IDParser2 >> raceID;

	destoyEquipmentSelectionControls();

	nameParser << "mouth\\" << mouthID  << ".png";
	imageName = nameParser.str();
	nameParser.str("");
	nameParser << "mouth\\" << mouthID << ".raw";
	dataName = nameParser.str();
	createAlignmentControls(getBodyPartPath(raceID,0,"Head"),imageName,dataName);
}

void equipAlignWindow::alignHairButton(wxCommandEvent &event) {
	int					hairID;
	std::stringstream	IDParser;
	std::string			imageName;
	std::string			dataName;
	std::stringstream	nameParser;
	int					raceID;

	IDParser << textBox_hairID->GetValue().c_str(); //Read the string from the text box into the stringstream
	IDParser >> hairID; //Extract the value from the string stream and cast it to an integer

	std::stringstream	 IDParser2;
	IDParser2 << textBox_raceSelect->GetValue().c_str(); //Get the race to align with
	IDParser2 >> raceID;

	destoyEquipmentSelectionControls();

	nameParser << "hair\\" << hairID << "\\" << "0.png";
	imageName = nameParser.str();
	nameParser.str("");
	nameParser << "hair\\" << hairID << "\\" << "calibration.raw";
	dataName = nameParser.str();
	createAlignmentControls(getBodyPartPath(raceID,0,"Head"),imageName,dataName);
}

void equipAlignWindow::alignfacialHairButton(wxCommandEvent &event) {
	int					hairID;
	std::stringstream	IDParser;
	std::string			imageName;
	std::string			dataName;
	std::stringstream	nameParser;
	int					raceID;

	IDParser << textBox_facialHairID->GetValue().c_str(); //Read the string from the text box into the stringstream
	IDParser >> hairID; //Extract the value from the string stream and cast it to an integer

	std::stringstream	 IDParser2;
	IDParser2 << textBox_raceSelect->GetValue().c_str(); //Get the race to align with
	IDParser2 >> raceID;

	destoyEquipmentSelectionControls();

	nameParser << "facialHair\\" << hairID << "\\" << "0.png";
	imageName = nameParser.str();
	nameParser.str("");
	nameParser << "facialHair\\" << hairID << "\\" << "calibration.raw";
	dataName = nameParser.str();
	createAlignmentControls(getBodyPartPath(raceID,0,"Head"),imageName,dataName);
}

void equipAlignWindow::alignEquipmentButton(wxCommandEvent &event) {
	int					equipmentID;
	std::stringstream	IDParser;
	std::string			imageName; //Name of the sprite to calibrate (eg. 0.png)
	std::string			dataName; //Name of the datafile associated with the sprite (eg. 0.raw)
	IDParser << textBox_equipmentID->GetValue().c_str(); //Read the string from the text box into the stringstream
	IDParser >> equipmentID; //Extract the value from the string stream and cast it to an integer
	switch (equipmentDataManager::equipmentList[equipmentID]->type) {
	case EQUIP_GLOVE: {

				std::vector<chooseablePart> partList;
				chooseablePart part;	
				std::stringstream nameParser;
				nameParser << "equipment\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-0.png";
				part.imageName= nameParser.str();
				nameParser.str("");
				nameParser << "equipmentSpriteData\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-0.raw";
				part.imageDataName = nameParser.str();
				partList.push_back(part);

				nameParser.str("");
				nameParser << "equipment\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-1.png";
				part.imageName= nameParser.str();
				nameParser.str("");
				nameParser << "equipmentSpriteData\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-1.raw";
				part.imageDataName = nameParser.str();
				partList.push_back(part);

				equipAlignChoosePart *partChooser = new equipAlignChoosePart(this);
				partChooser->partList = partList;
				partChooser->populateList();
				int Selection = partChooser->ShowModal();
				if (Selection!=-1) {
					imageName = partList[Selection].imageName;
					dataName =  partList[Selection].imageDataName;
				}
		break;
					  }


	case EQUIP_SHOE: {

				std::vector<chooseablePart> partList;
				chooseablePart part;	
				std::stringstream nameParser;
				nameParser << "equipment\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-0.png";
				part.imageName= nameParser.str();
				nameParser.str("");
				nameParser << "equipmentSpriteData\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-0.raw";
				part.imageDataName = nameParser.str();
				partList.push_back(part);

				nameParser.str("");
				nameParser << "equipment\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-1.png";
				part.imageName= nameParser.str();
				nameParser.str("");
				nameParser << "equipmentSpriteData\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-1.raw";
				part.imageDataName = nameParser.str();
				partList.push_back(part);

				equipAlignChoosePart *partChooser = new equipAlignChoosePart(this);
				partChooser->partList = partList;
				partChooser->populateList();
				int Selection = partChooser->ShowModal();
				if (Selection!=-1) {
					imageName = partList[Selection].imageName;
					dataName =  partList[Selection].imageDataName;
				}
			break;
	}

	 case EQUIP_SHOULDER: {

				std::vector<chooseablePart> partList;
				chooseablePart part;	
				std::stringstream nameParser;
				nameParser << "equipment\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-0.png";
				part.imageName= nameParser.str();
				nameParser.str("");
				nameParser << "equipmentSpriteData\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-0.raw";
				part.imageDataName = nameParser.str();
				partList.push_back(part);

				nameParser.str("");
				nameParser << "equipment\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-1.png";
				part.imageName= nameParser.str();
				nameParser.str("");
				nameParser << "equipmentSpriteData\\" << equipmentDataManager::equipmentList[equipmentID]->id << "-1.raw";
				part.imageDataName = nameParser.str();
				partList.push_back(part);

				equipAlignChoosePart *partChooser = new equipAlignChoosePart(this);
				partChooser->partList = partList;
				partChooser->populateList();
				int Selection = partChooser->ShowModal();
				if (Selection!=-1) {
					imageName = partList[Selection].imageName;
					dataName =  partList[Selection].imageDataName;
				}
			break;
	}

	default:
		{
			std::stringstream nameParser;
			nameParser << "equipment\\" << equipmentDataManager::equipmentList[equipmentID]->id << ".png";
			imageName = nameParser.str();
			nameParser.str("");
			nameParser << "equipmentSpriteData\\" << equipmentDataManager::equipmentList[equipmentID]->id << ".raw";
			dataName = nameParser.str();
			break;
		}
	}
	destoyEquipmentSelectionControls();
	createAlignmentControls(getBodyPartPath(0,0,equipmentDataManager::equipmentList[equipmentID]->id),imageName,dataName);
}

std::pair<std::string,std::string> equipAlignWindow::getBodyPartPath(int skinID, int skinColor, std::string partName) {
	std::stringstream		stringFormatter;
	std::string				bodyPartPath;
	std::string				bodyPartDataPath;

		stringFormatter.str("");
		stringFormatter << mainApplication::characterAssetPath << "race\\" << skinID << "\\skinColor\\" << skinColor << "\\" << partName << ".png";
		bodyPartPath = stringFormatter.str();
		stringFormatter.str("");
		stringFormatter << mainApplication::characterAssetPath << "race\\" << skinID <<  "\\" << partName << ".raw";
		bodyPartDataPath = stringFormatter.str();

		return std::pair<std::string,std::string>(bodyPartPath,bodyPartDataPath);
}
std::pair<std::string,std::string> equipAlignWindow::getBodyPartPath(int skinID, int skinColor, int equipID) {
	std::stringstream		stringFormatter;
	std::string				bodyPartPath;
	std::string				bodyPartDataPath;
	switch (equipmentDataManager::equipmentList[equipID]->type) {
	case EQUIP_BELT: case EQUIP_PANTS: case EQUIP_SHIRT: case EQUIP_SHOULDER: {
		stringFormatter.str("");
		stringFormatter << mainApplication::characterAssetPath << "race\\" << skinID << "\\skinColor\\" << skinColor << "\\" << "Body" << ".png";
		bodyPartPath = stringFormatter.str();
		stringFormatter.str("");
		stringFormatter << mainApplication::characterAssetPath << "race\\" << skinID <<  "\\" << "Body" << ".raw";
		bodyPartDataPath = stringFormatter.str();
		break;
	}
	 case EQUIP_GLOVE: {
		stringFormatter.str("");
		stringFormatter << mainApplication::characterAssetPath << "race\\" << skinID << "\\skinColor\\" << skinColor << "\\" << "LeftHand" << ".png";
		bodyPartPath = stringFormatter.str();
		stringFormatter.str("");
		stringFormatter << mainApplication::characterAssetPath << "race\\" << skinID <<  "\\" << "LeftHand" << ".raw";
		bodyPartDataPath = stringFormatter.str();
		break;
	}
	 case EQUIP_HELMET: {
		stringFormatter.str("");
		stringFormatter << mainApplication::characterAssetPath << "race\\" << skinID << "\\skinColor\\" << skinColor << "\\" << "Head" << ".png";
		bodyPartPath = stringFormatter.str();
		stringFormatter.str("");
		stringFormatter  << mainApplication::characterAssetPath<< "race\\" << skinID <<  "\\" << "Head" << ".raw";
		bodyPartDataPath = stringFormatter.str();
		break;
	}
	case EQUIP_SHOE: {
		wxString choices[2];
		choices[0] = "StraightFoot";
		choices[1] = "FacingFoot";
		wxSingleChoiceDialog* footSelect = new wxSingleChoiceDialog(this,_("Select which foot to calibrate With"),_("Select a foot type"),2,choices);
		footSelect->ShowModal();
		int  selection = footSelect->GetSelection();
		std::string footLoad = choices[selection];

		stringFormatter.str("");
		stringFormatter  << mainApplication::characterAssetPath << "race\\" << skinID << "\\skinColor\\" << skinColor << "\\" << footLoad << ".png";
		bodyPartPath = stringFormatter.str();
		stringFormatter.str("");
		stringFormatter << mainApplication::characterAssetPath << "race\\" << skinID <<  "\\" << footLoad << ".raw";
		bodyPartDataPath = stringFormatter.str();
		break;
	}

	}
	return std::pair<std::string,std::string>(bodyPartPath,bodyPartDataPath);
}

void equipAlignWindow::createAlignmentControls(std::pair<std::string,std::string> bodyPath, std::string imageName, std::string dataPath) {
	createAlignmentControls(bodyPath.first,bodyPath.second,imageName,dataPath);
}

void equipAlignWindow::createAlignmentControls(std::string bodyPartImagePath, std::string bodyPartDataPath, std::string imageName, std::string dataPath) {
	std::stringstream			stringFormatter;
	wxPNGHandler*			PNGHandler; //Handler for loading PNGs
	wxImage*				bodyPartImage; //Used for loading the body part
	wxImage*				equipmentImage; //USed for loading the equipment Image
	std::fstream			dataFile;//Used for reading/Writing data files.
	PNGHandler =			new wxPNGHandler();

	stringFormatter << mainApplication::characterAssetPath << imageName;
	fullImagePath = stringFormatter.str();
	stringFormatter.str("");
	stringFormatter << mainApplication::characterAssetPath << dataPath;
	fullDataPath = stringFormatter.str();

	bodyPartImage =			new wxImage();
	PNGHandler->LoadFile(bodyPartImage,wxFileStream(bodyPartImagePath.c_str()));
	bodyPartBitmap =		new wxBitmap(*bodyPartImage);
	bodyPartPosition=		new wxPoint(0,0);
	bodyPartSpriteOrigin =	new wxPoint(0,0);

	//Read the Sprite Origin
	dataFile.open(bodyPartDataPath,std::ios::binary | std::ios::in | std::ios::out);
	short readposX, readposY;
	dataFile.read((char*)&readposX,sizeof(short));
	dataFile.read((char*)&readposY,sizeof(short));
	bodyPartSpriteOrigin->x = readposX;
	bodyPartSpriteOrigin->y =  readposY;
	dataFile.close();


	equipmentImage =		new wxImage();
	PNGHandler->LoadFile(equipmentImage,wxFileStream(fullImagePath.c_str()));
	equipmentBitmap =		new wxBitmap(*equipmentImage);
	equipmentPosition =		new wxPoint(0,0);
	equipmentSpriteOrigin =	new wxPoint(equipmentBitmap->GetWidth()/2,equipmentBitmap->GetHeight()/2);

	//Read the Sprite Origin
	dataFile.open(fullDataPath,std::ios::binary | std::ios::in | std::ios::out);
	if (dataFile.is_open()) {
		short readposX, readposY;
		dataFile.read((char*)&readposX,sizeof(short));
		dataFile.read((char*)&readposY,sizeof(short));
		equipmentSpriteOrigin->x = readposX;
		equipmentSpriteOrigin->y = readposY;

		dataFile.read((char*)&readposX,sizeof(short));
		dataFile.read((char*)&readposY,sizeof(short));
		equipmentPosition->x = readposX;
		equipmentPosition->y = readposY;
		dataFile.close();
	}


	alignSizer = new wxBoxSizer(wxVERTICAL);
	alignmentRenderer = new equipAlignRenderer(this,this);
	saveButton = new wxButton(this,ID_BTN_SAVE,_("Save"));
	alignSizer->Add(alignmentRenderer,2,0);
	alignSizer->Add(saveButton,1,wxEXPAND);
	this->SetSizer(alignSizer);
	this->Layout();
	
}


void equipAlignWindow::keyDown(wxKeyEvent &event) {
	switch (event.GetKeyCode()) {
	case WXK_UP:
		this->equipmentPosition->y--;
		break;
	case WXK_DOWN:
		this->equipmentPosition->y++;
		break;
	case WXK_LEFT:
		this->equipmentPosition->x--;
		break;
	case WXK_RIGHT:
		this->equipmentPosition->x++;
		break;
	}
	this->alignmentRenderer->Refresh();
	event.Skip();
}

void equipAlignWindow::alignSaveButton(wxCommandEvent &event) {

	std::fstream dataFile(fullDataPath,std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
		dataFile.write((char*)&equipmentSpriteOrigin->x,sizeof(short));
		dataFile.write((char*)&equipmentSpriteOrigin->y,sizeof(short));
		short finalX = equipmentPosition->x;
		short finalY = equipmentPosition->y;
		dataFile.write((char*)&finalX ,sizeof(short));
		dataFile.write((char*)&finalY,sizeof(short));
		dataFile.close();
}