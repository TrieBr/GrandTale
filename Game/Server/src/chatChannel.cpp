#include "chatChannel.h"
#include "GTGameClient.h"


	chatChannel::chatChannel() {
	}
	chatChannel::~chatChannel() {
		if (pPlayerList.size()>0) {
			std::cout << "Destroying chatChannel with players still in list." << std::endl;
		}
	}
	void chatChannel::addPlayer(GTGameClient* player) {
		pPlayerList.push_back(player);
	}
	void chatChannel::removePlayer(GTGameClient* player) {
		for (unsigned int i=0; i<pPlayerList.size(); i++) {
			if (pPlayerList.at(i)==player) {
				pPlayerList.erase(pPlayerList.begin()+i);
				return;
			}
		}
	}

	void chatChannel::broadcastChatMessage(std::string author, std::string message, int color) {
		for (unsigned int i=0; i<pPlayerList.size(); i++) {
			pPlayerList.at(i)->sendChatMessage(author,message,color);
		}
	}
	void chatChannel::broadcastChatMessageWithSpeechBubble(std::string author, std::string message, GTGameClient* speechBubblePlayer, int color) {
		for (unsigned int i=0; i<pPlayerList.size(); i++) {
			pPlayerList.at(i)->sendChatMessageWithSpeechBubble(author,message,speechBubblePlayer, color);
		}
	}
