#include "ProgressSystem.h"
#include "DomSystem.h"
#include "GUIman.h"

ProgressSystem::ProgressSystem(DomSystem* domoticaSystem, GUIman* GuiSystem, const int maxPoints, const int interval, int money, const int moneyLoss, const int regenspeed) :
domSystem(domoticaSystem),
guiSystem(GuiSystem),
maxHitPoints(maxPoints),
currentHitPoints(maxPoints),
damageInterval(1),
damageMoment(0),
regenMultiplier(regenspeed),
inheritanceMoney(money),
inheritanceLoss(moneyLoss)
{

}

ProgressSystem::~ProgressSystem()
{

}

void ProgressSystem::setHitPoints(int points) {
	currentHitPoints = points;
}

void ProgressSystem::tick() {
	if (damageMoment == 0)
		setDamageMoment();
	else if (time(NULL) == damageMoment) {
		subtractHealth();
		subtractMoney();
		damageMoment = 0;
	}
}

void ProgressSystem::subtractHealth() {
	int currentNumberOfProblems = domSystem->giveList()->size();
	int totalDamage = 0;

	for (int i = 0; i < currentNumberOfProblems; i++){
		totalDamage += domSystem->giveList()->at(i)->healthDamage();
	}

	if (currentHitPoints > 0){
		setHitPoints(currentHitPoints - totalDamage + regenMultiplier);
	}

/*	if (currentNumberOfProblems == 0) {
		if (currentHitPoints < maxHitPoints && currentHitPoints > 0)
			setHitPoints(currentHitPoints + regenMultiplier);
		else {
			regenMultiplier = 0;
		}
	}
	else {
		if (currentHitPoints > 0)
			setHitPoints(currentHitPoints - currentNumberOfProblems * damageMultiplier);

		if (currentNumberOfProblems > regenMultiplier)
			regenMultiplier = currentNumberOfProblems;
	}*/

	normaliseHitpoints();

	std::string newHitPoints;
	newHitPoints = "Granny: " + std::to_string(currentHitPoints) + "%";
	guiSystem->setHealthCaption(newHitPoints);
}

void ProgressSystem::subtractMoney() {
	if (currentHitPoints > 0)
		inheritanceMoney -= inheritanceLoss;

	std::string newMoney = "$" + std::to_string(inheritanceMoney);

	guiSystem->setMoneyCaption(newMoney);
}

void ProgressSystem::normaliseHitpoints() {
	if (currentHitPoints > maxHitPoints)
		currentHitPoints = maxHitPoints;
	else if (currentHitPoints < 0)
		currentHitPoints = 0;
}

void ProgressSystem::setDamageMoment() {
	damageMoment = time(NULL) + damageInterval;
}

int ProgressSystem::getHitPoints() const {
	return currentHitPoints;
}
