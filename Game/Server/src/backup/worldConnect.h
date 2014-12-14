#include "packetProcessor.h"
#include "GTLoginClient.h"

class worldConnect : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTLoginClient &c) {
		unsigned char ticketBytes[8];
		ticketBytes[0] = rand() % 4294967295;
		ticketBytes[1] = rand() % 4294967295;
		ticketBytes[2] = rand() % 4294967295;
		ticketBytes[3] = rand() % 4294967295;
		ticketBytes[4] = rand() % 4294967295;
		ticketBytes[5] = rand() % 4294967295;
		ticketBytes[6] = rand() % 4294967295;
		ticketBytes[7] = rand() % 4294967295;
		std::cout << "[" << c.parentServer().getIdentifier() << "]" << "Generated Ticket: ";
		std::cout << std::hex << ticketBytes[0];
		std::cout << std::hex << ticketBytes[1];
		std::cout << std::hex << ticketBytes[2];
		std::cout << std::hex << ticketBytes[3];
		std::cout << std::hex << ticketBytes[4];
		std::cout << std::hex << ticketBytes[5];
		std::cout << std::hex << ticketBytes[6];
		std::cout << std::hex << ticketBytes[7];


		GTGameWorldClient* gameWorld =  ((GTLoginServer*)&c.parentServer())->gameWorldAcceptor.getClient(c.selectedWorld);
		RakNet::BitStream dataGS;
		dataGS.Write<RakNet::MessageID>(worldLoginInterfacePackets::PREPARE_TICKET);
		for(char i=0; i<8; i++) {
			dataGS.Write<unsigned char>(ticketBytes[i]); //TWrite byte of the ticket
		}
		//Custom Data
		dataGS.Write<int>(c.dbID); //User DBID
		dataGS.Write<int>(c.characterSlots[c.selectedCharacterSlot].dbID); //Character DBID
		gameWorld->sendPacket(dataGS);
		

		RakNet::BitStream datas; //The bitstream
		datas.Write<RakNet::MessageID>(loginPackets::GAMEWORLD_CONNECT); //Message ID
		for(char i=0; i<8; i++) {
			datas.Write<unsigned char>(ticketBytes[i]); //TWrite byte of the ticket
		}
		datas.Write<RakNet::RakString>(gameWorld->IP);
		datas.Write<short>(gameWorld->port);
		c.sendPacket(datas);


	}

};