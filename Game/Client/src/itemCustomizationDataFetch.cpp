#include "itemCustomizationDataFetch.h"
#include "gameServer.h"
std::vector<itemCustomizationFetchHandle*> itemCusomizationDataFetch::currentlyFetching;
int itemCusomizationDataFetch::fetchUID = 0;

itemCustomizationFetchHandle* itemCusomizationDataFetch::fetchItemCustomization(int customizationID) {
	itemCustomizationFetchHandle* handle = new itemCustomizationFetchHandle();
	handle->setFetchID(fetchUID);
	handle->setStatus(IC_FETCH_FETCHING);
	fetchUID++;
		if (fetchUID>100000) { //Wrap the fetch UID
			fetchUID = 0; //Set to 0
		}
	currentlyFetching.push_back(handle);
	networking::gameServer::item_fetchCustomizationData(customizationID, handle);
	return handle;

}

itemCustomizationFetchHandle* itemCusomizationDataFetch::getFetchHandleFromFetchID(int fetchID) {
	for (unsigned int i=0; i<currentlyFetching.size(); i++) {
		if (currentlyFetching[i]->getFetchID()==fetchID)
			return currentlyFetching[i];
	}
	return NULL;
}
void itemCusomizationDataFetch::removeFromFetching(int fetchID) {
	for (unsigned int i=0; i<currentlyFetching.size(); i++) {
		if (currentlyFetching[i]->getFetchID()==fetchID) {
			currentlyFetching.erase(currentlyFetching.begin()+i);
			return;
		}
	}

}