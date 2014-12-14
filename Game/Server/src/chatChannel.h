#include <vector>

#ifndef _H_CHATCHANNEL
#define _H_CHATCHANNEL

class GTGameClient;
class chatChannel { //A channel that players can chat in. Eg. Trade channel, general chat, party chat, etc.
public:
	chatChannel(); //Constructor
	~chatChannel(); //Destructor
	void addPlayer(GTGameClient* player);
	void removePlayer(GTGameClient* player);
	//Broadcasts a message to every client in the chatroom with specified author, message and optionally  text color.
	void broadcastChatMessage(std::string author, std::string message, int color = 0xFFFFFF);
	//Broadcasts a message to every client in the chatroom but displays a speechbubble above specified players head
	void broadcastChatMessageWithSpeechBubble(std::string author, std::string message, GTGameClient* speechBubblePlayer, int color = 0xFFFFFF);

private:
	std::vector<GTGameClient*> pPlayerList; //pointer to a vector of players

};

#endif