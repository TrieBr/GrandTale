#include "entityGUIChat.h"
#include "myData.h"
#include "gameServer.h"

namespace entities
{
	namespace GameGUI
	{

			entityGUIChat::entityGUIChat(){

				chatTypeBG = gameEngine::resources::graphics.loadBitmap(":gameGui:chatChatType.png");
				chatTextBoxBG = gameEngine::resources::graphics.loadBitmap(":gameGui:chatTextBox.png");
				font = gameEngine::resources::fonts.loadFont(":gameGui:mainFont.ttf",16);
				textEntryBox = new GUI::widgets::textbox(chatTextBoxBG,font,al_map_rgb(46,17,21));

			}
			void entityGUIChat::initialize(){
				drawLines = 7;
				lineHeight = 16;
				chatWidth = 310;
				resizingChatVertical = false;
				chatBoxCache = al_create_bitmap(310,lineHeight*drawLines+5);
				RenderChatBoxCache();
			}
			void entityGUIChat::cleanup(){
				delete textEntryBox;
			}
			void entityGUIChat::render(float oX,float oY){
			ALLEGRO_MOUSE_STATE mState; //Mouse state
			al_get_mouse_state(&mState); //Get the state of the mouse

			al_hold_bitmap_drawing(true);
			al_draw_bitmap(chatBoxCache,x,y-31-al_get_bitmap_height(chatBoxCache),0);

			if (resizingChatVertical || gameEngine::globalFunctions::pointInRegion(mState.x,mState.y,x,y-31-(drawLines*lineHeight)-7,x+chatWidth,y-31-(drawLines*lineHeight)+2)) {
				al_draw_line(x,y-31-al_get_bitmap_height(chatBoxCache),x+chatWidth,y-31-al_get_bitmap_height(chatBoxCache),al_map_rgb(255,255,255),1);
				al_draw_line(x,y-31-al_get_bitmap_height(chatBoxCache)+2,x+chatWidth,y-31-al_get_bitmap_height(chatBoxCache)+2,al_map_rgb(255,255,255),1);
			}

			al_draw_bitmap(chatTypeBG,x,y-26,0);
			textEntryBox->render(x+99,y-26,1);
			al_hold_bitmap_drawing(false);
				
			}
			void entityGUIChat::update(double _timeFactor){
				textEntryBox->update();
			}
			bool entityGUIChat::handleEvent(ALLEGRO_EVENT &e){
				if (e.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if (gameEngine::globalFunctions::pointInRegion(e.mouse.x,e.mouse.y,x+99,y-26,x+99+textEntryBox->getWidth(),y-26+textEntryBox->getHeight())) {
						textEntryBox->focus(true);
					}
					if (gameEngine::globalFunctions::pointInRegion(e.mouse.x,e.mouse.y,x,y-31-(drawLines*lineHeight)-7,x+chatWidth,y-31-(drawLines*lineHeight)+2)) {
						resizingChatVertical = true;
					}
				}
				if (e.type==ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
					if (resizingChatVertical) {
						resizingChatVertical = false;
					}
				}
				if (e.type==ALLEGRO_EVENT_KEY_DOWN) {
					if (e.keyboard.keycode==ALLEGRO_KEY_ENTER) {
						if (textEntryBox->isFocused()) {
							networking::gameServer::sendChatMessage(textEntryBox->Text);
							textEntryBox->Text = "";
						}
					}
				}
				if (e.type==ALLEGRO_EVENT_MOUSE_AXES) {
					if (resizingChatVertical) {
						drawLines = ((y-26)-e.mouse.y)/lineHeight;
						al_destroy_bitmap(chatBoxCache);
						chatBoxCache = al_create_bitmap(310,lineHeight*drawLines+5);
						RenderChatBoxCache();
						
					}
				}
				return false;
			}

			void entityGUIChat::AddMessage(std::string name, std::string message, float r, float g, float b){
				chatEntry e1;
				e1.Name = name;
				e1.Message = message;
				chatLog.push_back(e1);
				RenderChatBoxCache();
			}

			void entityGUIChat::RenderChatBoxCache(){
				ALLEGRO_BITMAP* returnBit = al_get_target_bitmap();
				al_set_target_bitmap(chatBoxCache);
				al_clear_to_color(al_map_rgba_f(0,0,0,0));
				short chatHeight = al_get_bitmap_height(chatBoxCache);
				al_draw_filled_rectangle(0,0,chatWidth,chatHeight,al_map_rgba_f(0,0,0,0.5));

				std::vector<formattedChatEntry> formattedChatLog;
				for(int i=0; i<chatLog.size(); i++) {
					if (al_get_text_width(font,std::string(chatLog[i].Name + ":").c_str()) + al_get_text_width(font,chatLog[i].Message.c_str()) > chatWidth) {
						formattedChatEntry fE;
						fE.r = chatLog[i].r;
						fE.g = chatLog[i].g;
						fE.b = chatLog[i].b;
						fE.Name = chatLog[i].Name + ":";
						fE.nameWidth = al_get_text_width(font,std::string(chatLog[i].Name + ":").c_str());
						fE.Message = chatLog[i].Message;
						size_t splitPoint;
						while (fE.nameWidth + al_get_text_width(font,fE.Message.c_str()) > chatWidth) {
							splitPoint = fE.Message.find_last_of(" ");
							if (splitPoint ==fE.Message.npos) {
								splitPoint = fE.Message.length()/2;
								fE.Message = fE.Message.substr(0,splitPoint);
							}else{
								fE.Message = fE.Message.substr(0,splitPoint);
							}
						}
						formattedChatLog.push_back(fE);
						formattedChatEntry fE2;
						fE2.r = chatLog[i].r;
						fE2.g = chatLog[i].g;
						fE2.b = chatLog[i].b;
						fE2.Name = "";
						fE2.nameWidth = al_get_text_width(font,std::string(chatLog[i].Name + ":").c_str());
						fE2.Message = std::string(chatLog[i].Message).substr(splitPoint,chatLog[i].Message.length()-splitPoint);
						formattedChatLog.push_back(fE2);

					}else{
						formattedChatEntry fE2;
						fE2.r = chatLog[i].r;
						fE2.g = chatLog[i].g;
						fE2.b = chatLog[i].b;
						fE2.Name = chatLog[i].Name + ":";
						fE2.nameWidth = al_get_text_width(font,std::string(chatLog[i].Name + ":").c_str());
						fE2.Message = std::string(chatLog[i].Message);
						formattedChatLog.push_back(fE2);
					}

				}

				float yy = 0;
				int linesDrawn = 0;
				for(int i = formattedChatLog.size()-1; i>=0 && (formattedChatLog.size()-1)-i<drawLines; --i) {
						al_draw_text(font,al_map_rgb_f(formattedChatLog[i].r,formattedChatLog[i].g,formattedChatLog[i].b),3,chatHeight-11-lineHeight+yy,0,formattedChatLog[i].Name.c_str());
					al_draw_text(font,al_map_rgb_f(formattedChatLog[i].r,formattedChatLog[i].g,formattedChatLog[i].b),5+formattedChatLog[i].nameWidth,chatHeight-11-lineHeight+yy,0,formattedChatLog[i].Message.c_str());
					yy-=lineHeight;
					linesDrawn++;
					if (linesDrawn>drawLines) {
						break;
					}
				}
				al_set_target_bitmap(returnBit);
			}


	}

}

