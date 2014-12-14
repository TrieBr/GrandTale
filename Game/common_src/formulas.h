#include <stats.h>
#include <weaponSize.h>
#include <mobSize.h>
#include <characterClass.h>
#ifndef _H_FORMULAS
#define  _H_FORMULAS

class formulas {
public:
	static float pointDistance(float x1, float y1, float x2, float y2);

	//Number of stat points to upgrade specified stat. (STAREQ)
	static unsigned char statRequiredToUpgrade(unsigned short currentStatLevel);
	//Calculates melee attack
		//stat_str : STAT_STR value
		//stat_dex : STAT_DEX value
		//weapon_dmg : The attack the equipped weapon gives
		//cardd_mod : Cars the amplify the output (this is a percentage of extra damage, 0 means no exra damage)
		//Weapon level : level of the weapon
		//weap_size : the size of the weapon (small, med or large);
		//mob_size : The size of the mob being attacked
	static unsigned short calculateMeleeAttack(unsigned short stat_str, unsigned short stat_dex, unsigned short weapon_dmg, float card_mod, unsigned char weap_lvl, unsigned char weap_size = WEAPON_MEDIUM, unsigned char mob_size = MOB_MEDIUM);   
	//Calculated magic attack
		//stat_int : STAT_INT value
	static unsigned short calculateMagicAttack(unsigned short stat_int);
	//Calculate Defence (FINDDEF)
		//armor_def : how much defence your armour gives
	static unsigned short calculateDefencePercent(unsigned short armor_def);
	//Calculate Magic Defence (FIMDEF)
		//armor_mdef : how much magic defence your armour gives
	static unsigned short calculateMagicDefencePercent(unsigned short armor_mdef);
	//Calculate max weight to carry
		//stat_str : STAT_STR value
		//level : level of mob/character, etc
	static unsigned short calculateWeight(unsigned short stat_str, unsigned short level);
	//Calculate hit
		//stat_dex : STAT_DEX value
		//level : level of mob/char, etc
	static unsigned short calculateHit(unsigned short stat_dex, unsigned short level);
	//Calculate Flee
		//stat_agi : STAT_AGI value
		//level : level of mob/char,etc
	static unsigned short calculateFlee(unsigned short stat_agi, unsigned short level);
	//Calculate the Max base health
		//stat_vit : STAT_VIT value
		//level : level of mob, char, etc
		//cType class type
	static unsigned int calculateMaxHealth(unsigned short stat_vit, unsigned short level, character::classType cType = character::CLASS_ALL);
	//Calculate crit chance
		//stat_luk : STAT_LUK value
	static float calculateCrit(unsigned short stat_luk);
	//Calculate max base mana
		//stat_int : STAT_INT value
		//level : level of char, mob, etc
		//cType : class type
	static unsigned int caclulateMaxMana(unsigned short stat_int, unsigned short level, character::classType cType = character::CLASS_ALL);
};

#endif