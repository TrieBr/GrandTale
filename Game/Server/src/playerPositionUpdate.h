
#include "packetProcessor.h"
#include "GTGameClient.h"
#include <iostream>
#include "GTGameServer.h"
#include "gameMap.h"

struct positionUpdate {
	float X;
	float Y;
	bool animationChanged;
	unsigned short animationID;
	float animationPosition;
	float animationBlend;
	bool left; //Direction
};

class playerPositionUpdate : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTGameClient &c) {
		RakNet::BitStream dataN;
		dataN.Write<RakNet::MessageID>(gamePackets::PLAYER_POSITIONUPDATE);
		positionUpdate x;
		data.Read<positionUpdate>(x);
		c.setX(x.X);
		c.setY(x.Y);
		data.ResetReadPointer();
		dataN.Write(data);
		dataN.Write<short>(c.UID);
		c.getCurrentMap()->broadcastPacket(dataN, &c);
	}

};