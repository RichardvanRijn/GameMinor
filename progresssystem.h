#pragma once

class DomSystem;

class ProgressSystem
{
public:
	ProgressSystem(DomSystem* domoticaSystem, const int maxPoints, const int interval, const int multiplier, int money, int moneyLoss);
	~ProgressSystem();

	void setHitPoints(int points);
	void setDamageMoment();
	void tick();

	int getHitPoints() const;
	
private:
	void normaliseHitpoints();
	void subtractHealth();
	void subtractMoney();

	int inheritanceMoney;
	const int inheritanceLoss;
	int currentHitPoints;
	int regenMultiplier;
	const int maxHitPoints;
	const int damageInterval;
	const int damageMultiplier;
	int damageMoment;
	DomSystem* domSystem;

};

