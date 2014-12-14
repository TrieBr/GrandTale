#include "packetProcessor.h"
#include "GTLoginClient.h"

class clientAuthenticate : public packetProcessor {
public:
	virtual void handle(RakNet::BitStream &data, GTLoginClient &c) {
		RakNet::RakString		username;
		RakNet::RakString		password;
		data.Read<RakNet::RakString>(username);
		data.Read<RakNet::RakString>(password);

		if (accountDB.query(RakNet::RakString("SELECT password,id FROM members WHERE username = '%s'",username.C_String()).C_String())) {
			if (accountDB.result().num_rows()>0) {
				std::string _password = password.C_String();
				if (accountDB.result()[0][0]==_password) {
					RakNet::BitStream data; //The bitstrea,
					data.Write<RakNet::MessageID>(loginPackets::CLIENT_AUTHENTICATE);
					data.Write<bool>(true); //Successfully authenticated
					c.sendPacket(data);
					c.authenticated = true; //Client is now authenticated
					c.dbID = accountDB.result()[0][1];
				}else{
					RakNet::BitStream data; //The bitstrea,
					data.Write<RakNet::MessageID>(loginPackets::CLIENT_AUTHENTICATE);
					data.Write<bool>(false); //Unable to authenticate
					c.sendPacket(data);
				}
			}else{//No rows returned, so account doesn't exist
				RakNet::BitStream data; //The bitstrea,
				data.Write<RakNet::MessageID>(loginPackets::CLIENT_AUTHENTICATE);
				data.Write<bool>(false); //Unable to authenticate
				c.sendPacket(data);
			}
		}

	}
};