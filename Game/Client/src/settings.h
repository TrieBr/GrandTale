/*
Settings for the game.
*/
#define SERVERIP "127.0.0.1"
#define SERVERPORT 1337
#ifdef _WIN32
#define ASSET_LOCATION "../../../../Assets/compiledAssets/"
#else 
#define ASSET_LOCATION ""
#endif


//GT PLATFORM CAN be
//#define GTIOS 1
#define GTWIN32 2
#define GTOSX 3
#define GTANDROID 4

#define GT_PLATFORM GTWIN32

#define RESOURCE_FILE_GRAPHICS "Graphics.gtd"
#define RESOURCE_FILE_AUDIO "Audio.gtd"
#define RESOURCE_FILE_FONTS "Fonts.gtd"
#define RESOURCE_FILE_DATA "Data.gtd"

#ifdef _WIN32
#define XPLATFORMITERATOR(a,b) std::map<a,b>::iterator
#else 
#define XPLATFORMITERATOR(a,b) std::_Rb_tree_iterator<std::pair<a, b> >
#endif