
#include <characterData.h>
#include "abstractClient.h"
#include <vector>

#ifndef _GTLOGINCLIENT_
#define _GTLOGINCLIENT_

#define CHARACTERSLOTS 3

struct charSlot {
	character::characterData cData;
	bool inUse;
	int dbID;
};

class GTLoginClient : public abstractClient {
public:
	GTLoginClient(RakNet::RakNetGUID &guid, abstractServer* parentServer, RakNet::RakPeerInterface*	clientInterface);
	void sendCharacterList();

	bool	authenticated; //Is the client authenticated with valid credentials?
	character::characterData cData;
	unsigned short selectedWorld;
	int dbID; //ID of this user in the database (set aftr authentication)
	std::vector<charSlot> characterSlots;
	char selectedCharacterSlot;
};

#endif