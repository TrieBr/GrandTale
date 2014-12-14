// ----------------------------------------------------------------------
// packet Identifiers. This .h file is used by both client and Server

// ------------------------------------------------------------------------



#include <MessageIdentifiers.h>


#ifndef _H_PACKETIDS_
#define   _H_PACKETIDS_
enum loginPacketIdentifiers
{
    AUTHENTICATE_REQUEST = ID_USER_PACKET_ENUM,
    AUTHENTICATE_RESULT,
    GAMESERVERLIST_REQUEST, //USed when the client needs the game server list sent to the,..
    CHARACTERLIST_REQUEST, //Used for sending/client requesting list of their characters
    CHARACTERCREATE,
    GAMESERVERLIST_SELECT, //Selected a server.. Tell the server what world we selected
    CHARACTERDELETE, //Delete a character.
    CHARACTERSELECT, //Select a character
    GAMESERVER_CONNECTREQUEST //Request gameServer connection info so we can connect to the game server
};

enum gamePacketIdentifiers
{
    AUTHENTICATETICKET_REQUEST = ID_USER_PACKET_ENUM,
    SEND_INITIAL_INFO, //Sends all the initial info to the player such as inventory items, equipment, character data, etc.
    MAP_GOTO, //GOTO a new map
    MAP_PLAYERDATA_INITIAL,
    PLAYER_POSITIONUPDATE
};



enum loginServerGameServerPacketIdentifiers //Packets between the game server and a login server
{
    UPDATE_GAMESERVER_INFO = ID_USER_PACKET_ENUM, //Game server sending info like capacity, name, etc. OR login server requesting it.
    GENERATE_TICKET
};

#endif