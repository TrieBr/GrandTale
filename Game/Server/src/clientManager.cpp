#include "clientManager.h"


unsigned char GetPacketIdentifier(RakNet::Packet *p) {
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	else
	return (unsigned char) p->data[0];
}
