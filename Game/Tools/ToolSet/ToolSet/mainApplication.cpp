

#include "mainApplication.h"
#include "applicationFrame.h"
#include <equipmentData.h>

std::string mainApplication::characterAssetPath;
	
bool mainApplication::OnInit() {
	equipmentDataManager::getAllEquipmentData("..\\..\\..\\..\\Game\\equipmentDatabase.s3db"); //Load the list
	mainApplication::characterAssetPath = "..\\..\\..\\..\\Game\\Assets\\rawAssets\\Graphics\\character\\";
	applicationFrame *frame = new applicationFrame( _("Grand Tale Developer Toolset"), wxPoint(50, 50), wxSize(800, 500) );
    frame->Show(true);
    SetTopWindow(frame);
	
	return true;
}