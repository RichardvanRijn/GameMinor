#pragma once

class DomSystem;
class GUIman;

class ProgressSystem
{
public:
	ProgressSystem(DomSystem* domoticaSystem, GUIman* GuiSystem ,const int maxPoints, const int interval, int money, const int moneyLoss, const int regenspeed);
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
	int damageMoment;
	DomSystem* domSystem;
	GUIman* guiSystem;

};

