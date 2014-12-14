#include <wx/wx.h>


class mainApplication: public wxApp
{
public:
    virtual bool OnInit();
	static std::string characterAssetPath;
};
