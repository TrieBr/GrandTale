#include <vector>
#include <itemCustomizationData.h>

/* controls fetching of item customization data from the server*/

#ifndef _H_CUSTOMIZATIONFETCH
#define _H_CUSTOMIZATIONFETCH

enum ItemCustomizationFetchStatus {
	IC_FETCH_FETCHING,
	IC_FETCH_DONE,
	IC_FETCH_ERROR
};

class itemCustomizationFetchHandle {
public:
	int getFetchID() { return fetchID; }
	void setFetchID(int id) { fetchID = id; }
	ItemCustomizationFetchStatus getStatus() { return status; }
	void setStatus(ItemCustomizationFetchStatus s) { status = s; }
	itemCustomizationData& getCustomizationData() { return data; }
private:
	int fetchID; //Unique ID used when fetching data
	ItemCustomizationFetchStatus status;
	itemCustomizationData data;
};


class itemCusomizationDataFetch {
public:
	static itemCustomizationFetchHandle* fetchItemCustomization(int customizationID);
	static itemCustomizationFetchHandle* getFetchHandleFromFetchID(int fetchID);
	static void removeFromFetching(int fetchID);
private:
	static std::vector<itemCustomizationFetchHandle*> currentlyFetching;
	static int fetchUID;
};

#endif