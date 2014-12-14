
#include <vector>
#include "gamePlayer.h"
#include "gameServer.h"
#include "gameEngineResources.h"
#include "mapData.h"
#ifndef _H_MAP
#define _H_MAP

class gamePlayer;
class map {
public:
	unsigned short uniqueID; //Unique map id. Map ID corresponds to the map data like tiles, etc (you can have multiple instances with same mapID)
	void addPlayer(gamePlayer *newPlayer); //Adds a new player to the map
	void loadMapData(); //Loads the map collision data, etc.
	void sendMapEntities(gamePlayer* client); //Sends map information (players, mobs, etc) to the specified client
	void sendPlayerList(gamePlayer* client); //Sends all the players in the map to the client
	void sendPlayerData(gamePlayer* player, gamePlayer* destination); //Sends info on a player in the map
	void broadcastPlayerData(gamePlayer* player); //Broadcasts a player to the whole map
	void broadcastPacket(RakNet::BitStream &data, gamePlayer* notInclude); //Broadcast a packet to everyone in the map
	void simulate(double timeStep); //Simulate the map

	mapData*			mData; //Map data that contains collision information ,etc
private:
		std::vector<gamePlayer*> playerList; //List of players in the map
		
};

#endif