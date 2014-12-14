// ----------------------------------------------------------------------
// entityServerSelect.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:
	The server select panel
*/
// ------------------------------------------------------------------------

#include "entityServerSelect.h"
#include "worldMainMenu.h"
#include "loginServer.h"

namespace entities
{
	namespace mainMenu
	{
			void entityServerSelect::initialize() {
				panelBG = gameEngine::resources::graphics.loadBitmap(":loadScreen:panelBG.png");
				panelBGCracks = gameEngine::resources::graphics.loadBitmap(":loadScreen:panelBGCracks.png");


				serverSelectText = gameEngine::resources::graphics.loadBitmap(":loadScreen:serverSelectText.png");
				backButton  = gameEngine::resources::graphics.loadBitmap(":loadScreen:backButton.png");
				scrollBarPlaceholder = gameEngine::resources::graphics.loadBitmap(":loadScreen:scrollBarPlaceholder.png");
				serverTitle = gameEngine::resources::graphics.loadBitmap(":loadScreen:serverTitle.png");
				serverButtonGo = gameEngine::resources::graphics.loadBitmap(":loadScreen:serverButtonGo.png");
				mainFont = gameEngine::resources::fonts.loadFont(":mainMenu:textbox.ttf",16);

			
				x = 277;
				y= 337;

				//Request the server list..
				networking::loginServer::requestGameServerList();

			}
			void entityServerSelect::cleanup() {

				for (unsigned i=0; i<serverList.size(); i++) {
					delete serverList[i]->goButton; //Delete te go button
					delete serverList[i];
				}
				serverList.clear();
			}
			void entityServerSelect::render(float oX,float oY) {
				//al_draw_tinted_bitmap(panelBGCracks,al_map_rgba_f(1*cracksAlpha,1*cracksAlpha,1*cracksAlpha,cracksAlpha),x-56,y-48,0);
				al_draw_bitmap(panelBG,x,y,0);
				al_draw_bitmap(serverSelectText,x+20,y+16,0);

				ALLEGRO_MOUSE_STATE mS;
				al_get_mouse_state(&mS);
				if (gameEngine::globalFunctions::pointInRegion(mS.x,mS.y,x+222,y+24,x+222+23,y+24+23)) { //If hovering over the back button
					al_draw_tinted_bitmap(backButton,al_map_rgba_f(1,1,1,0.8),x+222,y+24,0);
				}else{ //Not hovering, so draw it normally
					al_draw_tinted_bitmap(backButton,al_map_rgba_f(1,1,1,1),x+222,y+24,0);
				}
				
				al_draw_bitmap(scrollBarPlaceholder,x+216,y+50,0);

				float yy=50;
				int drawCount = 0;
				for (unsigned i=0; i<serverList.size(); i++) {
					al_draw_bitmap(serverTitle ,x+18,y+yy,0);
					al_draw_text(mainFont,al_map_rgb(46,17,22),x+18+6,y+yy,0,serverList[i]->serverName.c_str());
					serverList[i]->goButton->render(x+175,y+yy+4,1);
					yy+=36;
						drawCount++;
					if (drawCount>5) {
						break;
					}
				}

			}
			void entityServerSelect::update(double _timeFactor) {

				if (this->panelTransition.isTransitioning) {
					this->panelTransition.update(&x,&cracksAlpha, _timeFactor);
				}

				float yy=50;
				int drawCount = 0;
				for (unsigned i=0; i<serverList.size(); i++) {
					serverList[i]->goButton->update(x+175,y+yy+4);
					if (serverList[i]->goButton->fullClicked()) {
						networking::loginServer::selectServer(i); //Tell the server we have selected a game world						
					}
					yy+=36;
				}
			}

			bool entityServerSelect::handleEvent(ALLEGRO_EVENT &e) { 
				if (e.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{//Mouse was pressed
					if (e.mouse.button==1)
					{//Left clicked
						
						if (gameEngine::globalFunctions::pointInRegion(e.mouse.x,e.mouse.y,x+222,y+24,x+222+23,y+24+23)) {//Clicked on the "login" button
							if (!getParentWorld<worlds::worldMainMenu>()->showingError) { //If an error is now showing
								getParentWorld<worlds::worldMainMenu>()->serverSelectToLogin(); //Transition to the login panel
							}
						}
						

					}

				}
				return true;
			}

			void entityServerSelect::addServer(RakNet::RakString serverName, int id) {
				serverEntry* newS = new serverEntry;
				newS->serverName = serverName.C_String();
				newS->serverID = id;
				newS->goButton = new GUI::widgets::button(serverButtonGo,GUI::widgets::HOVER_HIGHLIGHT);

				serverList.push_back(newS);
			}
			

	}

}