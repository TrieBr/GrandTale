#include <vector>
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#endif
#include <string>
#include <BitStream.h>

#ifndef _H_SKILLCONTAINER
#define _H_SKILLCONTAINER

class SkillContainerEntry {
public:
	int uniqueID;
	int skillID;
	unsigned char skillLevel;
	virtual void readSkillContainerEntry(RakNet::BitStream &data) {
		data.Read<int>(uniqueID);
		data.Read<int>(skillID);
		data.Read<unsigned char>(skillLevel);
	}
	virtual void writeSkillContainerEntry(RakNet::BitStream &data) {
		data.Write<int>(uniqueID);
		data.Write<int>(skillID);
		data.Write<unsigned char>(skillLevel);
	}
};

class SkillContainerEntryExtended : public SkillContainerEntry {
public:
	float coolDown;

	virtual void readSkillContainerEntry(RakNet::BitStream &data) {
		this->::SkillContainerEntry::readSkillContainerEntry(data);
		data.Read<float>(coolDown);
	}
	virtual void writeSkillContainerEntry(RakNet::BitStream &data) {
		this->::SkillContainerEntry::writeSkillContainerEntry(data);
		data.Write<float>(coolDown);
	}
};

template <class T>
class SkillContainer {
public:
	void appendSkill(T newSkill) { skillList.push_back(newSkill); }
	int getSkillCount() { return skillList.size(); }
	T getSkill(int ind) { return skillList[ind]; }

	void readSkillContainer(RakNet::BitStream &data) {
		unsigned short containerSize;
		data.Read<unsigned short>(containerSize);
		for (int i=0; i<containerSize; i++) {
			T newEntry;
			newEntry.readSkillContainerEntry(data);
			skillList.push_back(newEntry);
		}
	}
	void writeSkillContainer(RakNet::BitStream &data) {
		data.Write<unsigned short>(skillList.size());
		for (unsigned int i=0; i<skillList.size(); i++) {
			skillList[i].writeSkillContainerEntry(data);
		}
	}
private:
	std::vector<T> skillList;
};

#endif