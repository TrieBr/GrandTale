
#include "entityGUISkills.h"
#include "myData.h"
#include "worldGameMap.h"

namespace entities
{
	namespace GameGUI
	{

			entityGUISkills::entityGUISkills() : abstractDraggableWindow(106,27){
				background = gameEngine::resources::graphics.loadBitmap(":gameGui:guiSkillBackground.png");
			closeButtonImage = gameEngine::resources::graphics.loadBitmap(":gameGui:guiCloseButton.png");
			tabPanels[0] = gameEngine::resources::graphics.loadBitmap(":gameGui:guiSkillsTabSkillsBackground.png");

			skillEntryTextBackground = gameEngine::resources::graphics.loadBitmap(":gameGui:skillTextBox.png");
			nameFont = gameEngine::resources::fonts.loadFont(":gameGui:mainFont.ttf",16);
			levelFont = gameEngine::resources::fonts.loadFont(":gameGui:mainFont.ttf",10);
			 closeButton = new GUI::widgets::button(closeButtonImage,GUI::widgets::HOVER_HIGHLIGHT);
			selectTab(0);
			RefreshSkills();
			}
			void entityGUISkills::initialize(){
				abstractDraggableWindow::addOpenWindow(this);
				abstractDraggableWindow::setWindowFront(this);
			}
			void entityGUISkills::cleanup(){
				delete closeButton;
				abstractDraggableWindow::closeOpenWindow(this);

			}
			void entityGUISkills::render(float oX,float oY){
			al_draw_bitmap(background,x,y,0);
			al_draw_bitmap(tabPanels[selectedTab],x+7,y+34,0);
			closeButton->render(x+212,y+5,1);
			skillSlotArray.Render(x,y);
				for (int i=0; i<myData::skills.getSkillHandlerCount(); i++) {
					al_draw_bitmap(skillEntryTextBackground,x+49,y+66+(i*30),0);
					al_draw_text(nameFont,al_map_rgb(0,0,0),x+49+6,y+66+(i*30)-4,0,globalData::getSkillManager()->GetSkill(myData::skills.getSkillHandlerAt(i)->getSkillID()).name.c_str());
					al_draw_textf(levelFont,al_map_rgb(192,12,12),x+49+6,y+66+(i*30)-4+17,0,"Level %i",myData::skills.getSkillHandlerAt(i)->getLevel());


				}
			}
			void entityGUISkills::update(double _timeFactor){
				closeButton->update(x+212,y+5);
				if (closeButton->fullClicked()) {
					gameEngine::core::getCurrentWorld<worlds::worldGameMap>()->closeGUIWindow_Skills();
				}
			}
			bool entityGUISkills::handleEvent(ALLEGRO_EVENT &e){
				dragHandleEvent(e);
				skillSlotArray.HandleEvent(e,x,y);
				if (e.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
					if (gameEngine::globalFunctions::pointInRegion2(e.mouse.x,e.mouse.y,x+7,y+34,65,27)) {
						selectTab(0);
					}
				}
				return false;
			}

			void entityGUISkills::selectTab(int id) {
				selectedTab = id;
			}

			void entityGUISkills::RefreshSkills() {
				skillSlotArray.rows = myData::skills.getSkillHandlerCount();
				skillSlotArray.editable = false;
				skillSlotArray.relative = true;
				skillSlotArray.x = 11;
				skillSlotArray.y = 64;
				skillSlotArray.rowSpacing = 38;
				skillSlotArray.colSpacing = 38;
				skillSlotArray.slots.clear();
				for (int i=0; i<myData::skills.getSkillHandlerCount(); i++) {
					skillSlotArray.slots.push_back(new Slot_SkillReference(myData::skills.getSkillHandlerAt(i)));
				}
			}
	}
}

