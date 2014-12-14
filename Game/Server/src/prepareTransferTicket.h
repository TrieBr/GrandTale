#include "packetProcessor.h"
#include "GTGameWorldClient.h"

class prepareTransferTicket : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTLoginServerClient &c) {

		transferTicket nTicket;
		for(char i=0; i<8; i++) {
			data.Read<unsigned char>(nTicket.ticketData[i]); //TWrite byte of the ticket
		}
		//Custom Data
		data.Read<int>(nTicket.userDBID); //User DBID
		data.Read<int>(nTicket.charDBID); //Character DBID

		((GTGameServer*)&c.parentServer())->ticketList.push_back(nTicket); //Add the ticket
	}

};