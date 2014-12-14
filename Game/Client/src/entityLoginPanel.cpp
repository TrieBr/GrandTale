// ----------------------------------------------------------------------
// entityLoginPanel.cpp
//     Copyright © Brad Triebwasser 2010
/* Description:
	The login panel on the main Menu
*/
// ------------------------------------------------------------------------

#include "entityLoginPanel.h"
#include "worldMainMenu.h"


namespace entities
{
	namespace mainMenu
	{
			void entityLoginPanel::initialize() {
				panelBG = gameEngine::resources::graphics.loadBitmap(":loadScreen:panelBG.png");
				

				usernameText = gameEngine::resources::graphics.loadBitmap(":loadScreen:usernameText.png");
				passwordText = gameEngine::resources::graphics.loadBitmap(":loadScreen:passwordText.png");
				loginButtonBitmap = gameEngine::resources::graphics.loadBitmap(":loadScreen:loginButton.png");
				exitButton = gameEngine::resources::graphics.loadBitmap(":loadScreen:exitButton.png");
				textbox = gameEngine::resources::graphics.loadBitmap(":loadScreen:textBox.png");
				panelBGCracks = gameEngine::resources::graphics.loadBitmap(":loadScreen:panelBGCracks.png");
				throbberIn = gameEngine::resources::graphics.loadBitmap(":loadScreen:ThrobberIn.png");
				throbberOut = gameEngine::resources::graphics.loadBitmap(":loadScreen:ThrobberOut.png");
				blankLoginButton = gameEngine::resources::graphics.loadBitmap(":loadScreen:loginButtonBlank.png");
				throbberInAngle = 0.0;
				throbberOutAngle = 0.0;

				textboxFont = gameEngine::resources::fonts.loadFont(":mainMenu:textbox.ttf",16);
				x = 277;
				y= 337;
				alpha = 0.0;
				cracksAlpha = 1;

				usernameBox = new GUI::widgets::textbox(textbox,textboxFont,al_map_rgb(46,17,22)); //Create the username Textbox
				usernameBox->focus(); //Focus it first
				passwordBox = new GUI::widgets::textbox(textbox,textboxFont,al_map_rgb(46,17,22)); //Create the password Textbox
				usernameBoxPosition = std::pair<float,float>(20,50);
				passwordBoxPosition = std::pair<float,float>(20,122);
				passwordBox->setReplacement('*');

				loginButton = new GUI::widgets::button(loginButtonBitmap,GUI::widgets::HOVER_HIGHLIGHT);

			}
			void entityLoginPanel::cleanup() {

	
				delete usernameBox;
				delete passwordBox;
				delete loginButton;

			}
			void entityLoginPanel::render(float oX,float oY) {
				//al_draw_tinted_bitmap(panelBGCracks,al_map_rgba_f(1*alpha*cracksAlpha,1*alpha*cracksAlpha,1*alpha*cracksAlpha,alpha*cracksAlpha),x-56,y-48,0);
				al_draw_tinted_bitmap(panelBG,al_map_rgba_f(1*alpha,1*alpha,1*alpha,alpha),x,y,0);
				al_draw_tinted_bitmap(usernameText,al_map_rgba_f(1*alpha,1*alpha,1*alpha,alpha),x+20,y+21,0);
				al_draw_tinted_bitmap(passwordText,al_map_rgba_f(1*alpha,1*alpha,1*alpha,alpha),x+20,y+93,0);

				ALLEGRO_MOUSE_STATE mS;
				al_get_mouse_state(&mS);

				
				if (networking::loginServer::connected) { //If we are connected, draw the login button..
					loginButton->render(x+21,y+164, alpha);
				}else{ //We arent connected so draw the loading throbber
					al_draw_bitmap(blankLoginButton,x+21,y+164,0);
					al_draw_rotated_bitmap(throbberIn,16,17,x+21+50,y+164+35,throbberInAngle,0);
					al_draw_rotated_bitmap(throbberOut,30,30,x+21+50,y+164+35,throbberOutAngle,0);
				}


				if (gameEngine::globalFunctions::pointInRegion(mS.x,mS.y,x+136,y+166,x+136+102,y+166+71)) {//govered on the "exit" button
					al_draw_tinted_bitmap(exitButton,al_map_rgba_f(1*alpha,1*alpha,1*alpha,0.8*alpha),x+136,y+166,0);
				}else{
					al_draw_tinted_bitmap(exitButton,al_map_rgba_f(1*alpha,1*alpha,1*alpha,1*alpha),x+136,y+166,0);
				}

				



				usernameBox->render(x+usernameBoxPosition.first,y+usernameBoxPosition.second); //Render the username Box
				passwordBox->render(x+passwordBoxPosition.first,y+passwordBoxPosition.second); //Render the password Box

			}
			void entityLoginPanel::update(double _timeFactor) {

				usernameBox->update(); //Update the username Box
				passwordBox->update(); //Update the password Box

				if (networking::loginServer::connected) { //If we are connected, update the login button..
					loginButton->update(x+21,y+164);
					if (loginButton->fullClicked()) {
						if (!getParentWorld<worlds::worldMainMenu>()->showingError) { //If an error is now showing
								networking::loginServer::authenticate(usernameBox->Text, passwordBox->Text);
								}
					}
				}else{ //Not connected, so update the throbber
					throbberInAngle+= 0.04*_timeFactor;
					throbberOutAngle-= 0.04*_timeFactor;
				}

				
				if (alpha<1)
				{
					alpha += 0.04 * _timeFactor;
					if (alpha>1)
					{
						alpha = 1;
					}
				}
				if (this->panelTransition.isTransitioning) { //If we are transitioning
					this->panelTransition.update(&x,&cracksAlpha, _timeFactor);
				}
				
			}

			
			bool entityLoginPanel::handleEvent(ALLEGRO_EVENT &e) { 
				if (e.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{//Mouse was pressed
					if (e.mouse.button==1)
					{//Left clicked
						if (gameEngine::globalFunctions::pointInRegion(e.mouse.x,e.mouse.y,x+usernameBoxPosition.first,y+usernameBoxPosition.second,x+usernameBoxPosition.first+180,y+usernameBoxPosition.second+31)) {//Mouse in region of username Box
							usernameBox->focus(true);
							passwordBox->focus(false);
						}
						if (gameEngine::globalFunctions::pointInRegion(e.mouse.x,e.mouse.y,x+passwordBoxPosition.first,y+passwordBoxPosition.second,x+passwordBoxPosition.first+180,y+passwordBoxPosition.second+31)) {//Mouse in region of password Box
							passwordBox->focus(true);
							usernameBox->focus(false);
						}
						/*if (gameEngine::globalFunctions::pointInRegion(e.mouse.x,e.mouse.y,x+21,y+164,x+21+102,y+164+71)) {//Clicked on the "login" button
							if (!getParentWorld<worlds::worldMainMenu>()->showingError) { //If an error is now showing
							networking::loginServer::authenticate(usernameBox->Text, passwordBox->Text);
							}
						}*/

						if (gameEngine::globalFunctions::pointInRegion(e.mouse.x,e.mouse.y,x+136,y+166,x+136+102,y+166+71)) {//Clicked on the "exit" button
							if (!getParentWorld<worlds::worldMainMenu>()->showingError) { //If an error is now showing
								gameEngine::logger::logStream << "Game display closed via entityLoginPanel ecit button" << endl;
								gameEngine::core::shutdown();
							}
						}


					

					}

				}
				return true;
			}

			

			

	}

}