#include "RandomBonusModifier.h"
#include <cstdlib>

int RandomBonusModifier::apply(int currentScore) {
    int bonus = (rand() % 91) + 10; // random 10-100
    return currentScore + bonus;
}

std::string RandomBonusModifier::getName() const {
    return "LuckyBoost";
}

std::string RandomBonusModifier::getDescription() const {
    return "Menambah bonus acak antara +10 hingga +100";
}

IModifier* RandomBonusModifier::clone() const {
    return new RandomBonusModifier(*this);
}
