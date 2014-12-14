
#include <wx/wx.h>
#include <string>
#include <vector>

#ifndef _H_ALIGNCHOOSEPART
#define _H_ALIGNCHOOSEPART

struct chooseablePart {
	std::string imageName;
	std::string imageDataName;
};
enum {
	ID_LISTBOX
};

class equipAlignChoosePart : public wxDialog {
public:
	equipAlignChoosePart(wxWindow *parent);
	~equipAlignChoosePart();
	std::vector<chooseablePart> partList;
	void populateList();


	
	void selectChoice(wxCommandEvent &event);
    DECLARE_EVENT_TABLE()

private:
	wxListBox *			listBox;

};


#endif