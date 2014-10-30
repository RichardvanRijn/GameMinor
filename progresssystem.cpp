#include "progresssystem.h"
#include "DomSystem.h"

ProgressSystem::ProgressSystem(DomSystem* domoticaSystem, const int maxPoints, const int interval, const int multiplier, int money, const int moneyLoss) :
	domSystem(domoticaSystem),
	maxHitPoints(maxPoints),
	currentHitPoints(maxPoints),
	damageInterval(1),
	damageMoment(0),
	damageMultiplier(multiplier),
	regenMultiplier(0),
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

	if (currentNumberOfProblems == 0) {
		if (currentHitPoints < maxHitPoints && currentHitPoints > 0)
			setHitPoints(currentHitPoints + damageMultiplier * regenMultiplier);
		else {
			regenMultiplier = 0;
		}
	}
	else {
		if (currentHitPoints > 0)
			setHitPoints(currentHitPoints - currentNumberOfProblems * damageMultiplier);

		if (currentNumberOfProblems > regenMultiplier)
			regenMultiplier = currentNumberOfProblems;
	}

	normaliseHitpoints();

	std::cout << "Hitpoints: " << currentHitPoints << std::endl;
}

void ProgressSystem::subtractMoney() {
	if (currentHitPoints > 0)
		inheritanceMoney -= inheritanceLoss;

	std::cout << "Money: " << inheritanceMoney << std::endl;
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
