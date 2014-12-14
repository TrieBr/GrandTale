#include "tooltipManager.h"

tooltip* tooltipManager::currentTooltip;
 bool     tooltipManager::deleteOnChange; //Delete the tooltip object when changed
void tooltipManager::initialize() {
	currentTooltip  = NULL;
	deleteOnChange = false;
}
void tooltipManager::cleanup() {
	if (currentTooltip!=NULL) currentTooltip->cleanup();
}
void tooltipManager::setTooltip(tooltip *p, bool deleteOnChange) {
	if (currentTooltip!=NULL) { currentTooltip->cleanup(); if (tooltipManager::deleteOnChange) delete currentTooltip; }
	currentTooltip = p;
	tooltipManager::deleteOnChange = deleteOnChange;
	if (currentTooltip!=NULL) currentTooltip->initialize();
}
tooltip* tooltipManager::getTooltip() {
	return currentTooltip;
}
void tooltipManager::renderTooltip(float X, float Y) {
	if (currentTooltip!=NULL) currentTooltip->render(X,Y);
}
void tooltipManager::updateTooltip(double delta) {
	if (currentTooltip!=NULL) currentTooltip->update(delta);
}