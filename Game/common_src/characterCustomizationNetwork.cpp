#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include <string>
#include <BitStream.h>
#include <characterCustomization.h>

namespace character {
void characterCustomization::readCharacterCustomization(RakNet::BitStream &data) {
			data.Read<unsigned char>(hairType); //Read the ID
			data.Read<unsigned char>(hairColor); //Read the ID
			data.Read<unsigned char>(eyeType); //Read the ID
			data.Read<unsigned char>(mouthType); //Read the ID
			data.Read<unsigned char>(facialHairType); //Read the ID
			data.Read<unsigned char>(skinColor); //Read the ID
			data.Read<unsigned char>(race); //Read the ID
			data.Read<unsigned char>(gender); //Read the ID
			data.Read<bool>(drawOffHandInFront); //Read the ID
			data.Read<bool>(drawMainHandInFront); //Read the ID
			data.Read<unsigned char>(characterClass); //Read the ID
			data.Read<unsigned char>(characterFaction); //Read the ID

			data.Read<int>(equipment[EQUIP_BELT]);
			data.Read<int>(equipment[EQUIP_GLOVE]);
			data.Read<int>(equipment[EQUIP_HELMET]);
			data.Read<int>(equipment[EQUIP_PANTS]);
			data.Read<int>(equipment[EQUIP_SHIRT]);
			data.Read<int>(equipment[EQUIP_SHOE]);
			data.Read<int>(equipment[EQUIP_SHOULDER]);
			data.Read<int>(equipment[EQUIP_OFFHAND]);
			data.Read<int>(equipment[EQUIP_RANGED]);
			data.Read<int>(equipment[EQUIP_RING]);
			data.Read<int>(equipment[EQUIP_RING2]);
			data.Read<int>(equipment[EQUIP_MAINHAND]);
			data.Read<int>(equipment[EQUIP_TRINKET]);
			data.Read<int>(equipment[EQUIP_HEAD_LOWER]);


		}
		void characterCustomization::writeCharacterCustomization(RakNet::BitStream &data) {
			data.Write<unsigned char>(hairType);
			data.Write<unsigned char>(hairColor);
			data.Write<unsigned char>(eyeType);
			data.Write<unsigned char>(mouthType);
			data.Write<unsigned char>(facialHairType);
			data.Write<unsigned char>(skinColor);
			data.Write<unsigned char>(race);
			data.Write<unsigned char>(gender);
			data.Write<bool>(drawOffHandInFront);
			data.Write<bool>(drawMainHandInFront);
			data.Write<unsigned char>(characterClass);
			data.Write<unsigned char>(characterFaction);

			data.Write<int>(equipment[EQUIP_BELT]);
			data.Write<int>(equipment[EQUIP_GLOVE]);
			data.Write<int>(equipment[EQUIP_HELMET]);
			data.Write<int>(equipment[EQUIP_PANTS]);
			data.Write<int>(equipment[EQUIP_SHIRT]);
			data.Write<int>(equipment[EQUIP_SHOE]);
			data.Write<int>(equipment[EQUIP_SHOULDER]);
			data.Write<int>(equipment[EQUIP_OFFHAND]);
			data.Write<int>(equipment[EQUIP_RANGED]);
			data.Write<int>(equipment[EQUIP_RING]);
			data.Write<int>(equipment[EQUIP_RING2]);
			data.Write<int>(equipment[EQUIP_MAINHAND]);
			data.Write<int>(equipment[EQUIP_TRINKET]);
			data.Write<int>(equipment[EQUIP_HEAD_LOWER]);
		}

}