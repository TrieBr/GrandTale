
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include <map>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include "packetProcessor.h"
#include <vector>
#include <stdexcept>
#include <iostream>

#ifdef _WIN32

#define XPLATFORMITERATOR(a,b) std::map<a,b>::iterator
#else 
#define XPLATFORMITERATOR(a,b) std::_Rb_tree_iterator<std::pair<const a, b> >
#endif

#ifndef _CLIENTACCEPTOR_
#define  _CLIENTACCEPTOR_
class abstractServer;

unsigned char GetPacketIdentifier(RakNet::Packet *p);

template <class T>
class clientManager {
public:
	void start(abstractServer* parent, short listenPort) {
		parentServer = parent;
		clientInterface = RakNet::RakPeerInterface::GetInstance(); //Get a new peer interface
		RakNet::StartupResult sRes = clientInterface->Startup(255,new RakNet::SocketDescriptor(listenPort,0),1); //Startup the interface
		//clientInterface->ApplyNetworkSimulator(0.0,500,5);
		if (sRes==RakNet::RAKNET_STARTED) { //If started sucessfully
			clientInterface->SetMaximumIncomingConnections(255); //Set the max number of connections
		}
	}

	void connect(abstractServer* parent, std::string IP, short port) {
		parentServer = parent;
		RakNet::StartupResult		sRes;
		clientInterface = RakNet::RakPeerInterface::GetInstance(); //Get a new peer interface
		sRes = clientInterface->Startup(1,new RakNet::SocketDescriptor(), 1); //Startup the interface
		RakNet::ConnectionAttemptResult cRes = clientInterface->Connect(IP.c_str(),port,0,0); //Connect to the login server server
	}

	clientManager() {}
	void handle() {
		RakNet::Packet *packet = clientInterface->Receive(); //Attempt to receive a packet
		if (packet!=NULL){ //If a packet was received
			unsigned char packetID = GetPacketIdentifier(packet); //Get the packet ID
				switch (packetID) {
					case ID_NEW_INCOMING_CONNECTION: {
							T* newClient = new T(packet->guid,parentServer,this->clientInterface);
							addClient(packet->guid,newClient);
							break;
						}
					case ID_CONNECTION_REQUEST_ACCEPTED: {
							T* newClient = new T(packet->guid,parentServer,this->clientInterface);
							addClient(packet->guid,newClient);
							break;
						}
					default: {
						RakNet::BitStream data(packet->data+sizeof(RakNet::MessageID),packet->length-sizeof(RakNet::MessageID),false);
						try {
							packetProcessor * p = packetProcessorList.at((int)packetID);
							if (p!=NULL) {
								p->handle(data,*clientList[packet->guid]); //Handle the packet using the player's object
							}
						} catch (std::out_of_range &e) {
							std::cout << "Unhandled packet: " << (int)packetID << ". out_of_range exeption thrown on handler lookup." << e.what() << std::endl;
						}
						break;
							 }
				}
			clientInterface->DeallocatePacket(packet); //Deallocate the packet
		}
	}
	~clientManager() { 
		for (XPLATFORMITERATOR(RakNet::RakNetGUID,T*) i=clientList.begin(); i!=clientList.end(); i++) {
			delete i->second;
		}
		for (unsigned int i = 0; i <packetProcessorList.size(); i++) {
			if (packetProcessorList[i]!=NULL) {
				delete packetProcessorList[i];
			}
		}
	}

	void registerPacketProcessor(int opCode, packetProcessor* handler) {
			if ((unsigned int)opCode >= packetProcessorList.size()) {
				packetProcessorList.resize(opCode+1,NULL);
			}
			packetProcessorList[opCode] = handler;
		}

	unsigned int getClientCount() {
		return clientList.size();
	}

	T* getClient(unsigned int ind) {
		unsigned int count = 0;
		for (XPLATFORMITERATOR(RakNet::RakNetGUID,T*) i = clientList.begin(); i!=clientList.end(); i++) {
			if (count==ind) {
				return i->second;
			}
			count ++;
		}
		return NULL;
	}
	
private:
	RakNet::RakPeerInterface*		clientInterface;
	std::map<RakNet::RakNetGUID,T*>	clientList;
	abstractServer* parentServer;
	void addClient(RakNet::RakNetGUID guid, T* newClient) {
		clientList[guid] = newClient;
	}
	std::vector<packetProcessor*>	packetProcessorList;
};

#endif