#include <formulas.h>
#include <cmath>
#define sqrtf sqrt

float formulas::pointDistance(float x1, float y1, float x2, float y2) {
	return sqrtf(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
}

//Number of stat points to upgrade specified stat. (STAREQ)
	unsigned char formulas::statRequiredToUpgrade(unsigned short currentStatLevel) {
		return 2+(2*(currentStatLevel/5));
	}

	unsigned short formulas::calculateMeleeAttack(unsigned short stat_str, unsigned short stat_dex, unsigned short weapon_dmg, float card_mod, unsigned char weap_lvl, unsigned char weap_size, unsigned char mob_size) {
		 float STRDMG = stat_str + (0.01*(((stat_str*stat_str))/2));
		 float DEXMUL = (double)((double)((double)stat_dex*0.1)+100)/100;
		 int WEPDMG = weapon_dmg;
		 float CARDMOD = card_mod + 1;
		 float SIZMOD = 1;
			if (weap_size==mob_size) SIZMOD = 1;
			if (weap_size==WEAPON_SMALL && (mob_size==MOB_MEDIUM)) SIZMOD = 0.95;
			if (weap_size==WEAPON_SMALL && (mob_size==MOB_LARGE)) SIZMOD = 0.90;
			if (weap_size==WEAPON_MEDIUM && (mob_size==MOB_SMALL)) SIZMOD = 0.95;
			if (weap_size==WEAPON_MEDIUM && (mob_size==MOB_LARGE)) SIZMOD = 0.95;
			if (weap_size==WEAPON_LARGE && (mob_size==MOB_SMALL)) SIZMOD = 0.90;
			if (weap_size==WEAPON_LARGE && (mob_size==MOB_MEDIUM)) SIZMOD = 0.95;
		return STRDMG + ((float)SIZMOD*((((float)CARDMOD*(float)WEPDMG)*(float)weap_lvl)*(float)DEXMUL));
	}
	unsigned short formulas::calculateMagicAttack(unsigned short stat_int) {
		return (float)5*((float)stat_int/(float)4);
	}
	unsigned short formulas::calculateDefencePercent(unsigned short armor_def) {
			return (1.0f - ((float)armor_def/5.0f))*100;
	}

	unsigned short formulas::calculateMagicDefencePercent(unsigned short armor_mdef) {
		return (1.0f - ((float)armor_mdef/5.0f))*100;
	}
	unsigned short formulas::calculateWeight(unsigned short stat_str, unsigned short level) {
		return 1500.0f + ((((float)stat_str/5.0f)+((float)level/5.0f))*100);
	}
	unsigned short formulas::calculateHit(unsigned short stat_dex, unsigned short level) {
		return 50.0f +(((float)stat_dex*2.0f)+(float)level);
	}
	unsigned short formulas::calculateFlee(unsigned short stat_agi, unsigned short level) {
		return 50.0f + (((float)stat_agi*2.0f)+(float)level);
	}
	unsigned int formulas::calculateMaxHealth(unsigned short stat_vit, unsigned short level, character::classType cType) {
		
		float CLASSMODHP = 1.7;

		
		return ((50.0f * CLASSMODHP)*2.0f)*((float)level/3.0f)*((((float)stat_vit*1.5f)/100.0f)+1.0f);

	}
	float formulas::calculateCrit(unsigned short stat_luk) {
		return 1.0f+((float)stat_luk*0.3f);
	}
	unsigned int formulas::caclulateMaxMana(unsigned short stat_int, unsigned short level, character::classType cType ) {
		float baseMP = level*100;
		return (float)baseMP*(1.0f+(((float)stat_int*1.5f)/100));
	}