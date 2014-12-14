#include <MessageIdentifiers.h>

#ifndef _PACKETOPS_
#define _PACKETOPS_

namespace loginPackets {

enum login {
	CLIENT_AUTHENTICATE = ID_USER_PACKET_ENUM,
	REQUEST_WORLDLIST,
	REQUEST_CHARACTERLIST,
	CHARACTER_CREATE,
	WORLDLIST_SELECT,
	CHARACTER_DELETE,
	CHARACTER_SELECT,
	GAMEWORLD_CONNECT,
	STAT_COMMANDS,
};

}

namespace gamePackets {

enum game {
	TICKET_VERIFY= ID_USER_PACKET_ENUM,
	INITIAL_INFOLOAD,
	MAP_GOTO,
	PLAYER_CHARACTER_DATA,
	PLAYER_POSITIONUPDATE,
	PLAYER_CHAT,
	PLAYER_UPDATE_CUSTOMIZATION,
	ITEM_CONTAINER_ACTION,
	EQUIPMENT_ACTION,
	SKILLHANDLER_ACTION,
	COMBAT_ENTITY,
	ITEM_CUSTOMIZATION_FETCH,
	STAT_COMMAND,
	MISC_DATA_UPDATE
};
enum COMBAT_ENTITY_ACTIONS {
	COMBAT_ENTITY_CREATE,
	COMBAT_ENTITY_UPDATE,
	COMBAT_ENTITY_HIT
};

enum ITEM_CONTAINER_ACTIONS {
	ITEM_CONTAINER_SWAP_SLOTS,
	ITEM_CONTAINER_UPDATE_SLOT
};

enum EQUIPMENT_ACTIONS {
	EQUIP_FROM_ITEM_CONTAINER
};

enum SKILLHANDLER_ACTIONS {
	SKILL_CLIENTADD,
	SKILL_EXECUTED
};

enum STATCOMMANDS_ACTIONS {
	STAT_COMMAND_INCREASE_STAT,
	STAT_UPDATE,
};

}

namespace worldLoginInterfacePackets {

enum worldLogin {
	WORLD_SEND_DATA = ID_USER_PACKET_ENUM,
	PREPARE_TICKET

};

}

#endif