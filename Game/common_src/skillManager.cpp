#include <skillManager.h>

void skillManager::allocateSkills(int size) {
	skills = new skillData[size];
	skillCount = size;
}

skillData skillManager::GetSkill(int id){
	return skills[id];
}
void skillManager::SetSkill(int id, skillData &skill){
	skills[id] = skill;
}
