#include "equipAlignChoosePart.h"



BEGIN_EVENT_TABLE(equipAlignChoosePart, wxDialog)
	EVT_LISTBOX_DCLICK(ID_LISTBOX,  equipAlignChoosePart::selectChoice)
END_EVENT_TABLE()


equipAlignChoosePart::equipAlignChoosePart(wxWindow *parent) 
	:wxDialog(parent,_("Choose Part"), true,-1,-1,200,200,wxTHICK_FRAME | wxCAPTION)
{
	listBox = new wxListBox(this,ID_LISTBOX,wxDefaultPosition,wxSize(200,200));
	this->SetReturnCode(0);
}





equipAlignChoosePart::~equipAlignChoosePart() {

}

void equipAlignChoosePart::populateList() {
	for (unsigned int i=0; i<this->partList.size(); i++) {
		listBox->Insert(_(this->partList[i].imageName.c_str()),listBox->GetCount());
	}
}

void equipAlignChoosePart::selectChoice(wxCommandEvent &event) {

	std::string imageNameFind = listBox->GetString(listBox->GetSelection()).c_str();
	for (unsigned int i=0; i<this->partList.size(); i++) {
		if (this->partList[i].imageName==imageNameFind) {
			this->EndModal(i);
		}
	}

}