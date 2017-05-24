#pragma once

class Stats
{
public:
	Stats(float hp_, float emp_, float dmg_min_, float dmg_max_, unsigned int def_, int str_, int dur_, int dex_, int agi_, int wis_, int chr_)
	{
		hp = hp_;
		emp = emp_;

		dmg_min = dmg_min_;
		dmg_max = dmg_max_;

		def = def_;

		str = str_;
		dur = dur_;
		dex = dex_;
		agi = agi_;
		wis = wis_;
		chr = chr_;
	}
	// podstawowe statystyki, wspólne dla przedmiotów i wszystkich postaci nie bêd¹cych NPC

	float hp;	// punkty zdrowia
	float emp;	// punkty energii lub many w zale¿noœci od klasy postaci

	float dmg_min;
	float dmg_max;

	unsigned int def;
	
	int str;
	int dur;
	int dex;
	int agi;
	int wis;
	int chr;
};

class StatsHero
{
public:
	// statystyki z za³o¿onym ekwipunkiem
	int str_eq;
	int dur_eq;
	int dex_eq;
	int agi_eq;
	int wis_eq;
	int chr_eq;

	// bazowe mno¿niki statystyk zale¿ne od klasy postaci
	float str_b;
	float dur_b;
	float dex_b;
	float agi_b;
	float wis_b;
	float chr_b;
};

class StatsSkill
{
public:
	StatsSkill(float hp_, float hpRegen_, short int hpRegenDuration_, float emp_, float empRegen_, short int empRegenDuration_, unsigned int def_, float defMultipler_, short int defMultiplerDuration_, float dmgGivenMultipler_, short int dmgGivenMultiplerDuration_, float dmgTakenMultipler_, short int dmgTakenMultiplerDuration_, float doubleStrikeChance_, short int doubleStrikeDuration_, float bleedingChance_, short int bleedingDuration_, bool unblockable_, bool fallback_)
	{
		hp = hp_;
		hpRegen = hpRegen_;
		hpRegenDuration = hpRegenDuration_;

		emp = emp_;
		empRegen = empRegen_;
		empRegenDuration = empRegenDuration_;

		def = def_;
		defMultipler = defMultipler_;
		defMultiplerDuration = defMultiplerDuration_;

		dmgGivenMultipler = dmgGivenMultipler_;
		dmgGivenMultiplerDuration = dmgGivenMultiplerDuration_;
		dmgTakenMultipler = dmgTakenMultipler_;
		dmgTakenMultiplerDuration = dmgTakenMultiplerDuration_;
		doubleStrikeChance = doubleStrikeChance_;
		doubleStrikeDuration = doubleStrikeDuration_;
		bleedingChance = bleedingChance_;
		bleedingDuration = bleedingDuration_;
		unblockable = unblockable_;
		fallback = fallback_;
	}

	int hp;
	float hpRegen;
	short int hpRegenDuration;

	int emp;
	float empRegen;
	short int empRegenDuration;
	
	int def;
	float defMultipler;
	short int defMultiplerDuration;

	float dmgGivenMultipler;
	short int dmgGivenMultiplerDuration;

	float dmgTakenMultipler;
	short int dmgTakenMultiplerDuration;
	
	float doubleStrikeChance;
	short int doubleStrikeDuration;

	float bleedingChance;
	short int bleedingDuration;

	bool unblockable;

	bool fallback;
};