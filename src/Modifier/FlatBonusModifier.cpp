#include "FlatBonusModifier.h"

FlatBonusModifier::FlatBonusModifier(int amount) : bonusAmount(amount) {}

int FlatBonusModifier::apply(int currentScore) {
    return currentScore + bonusAmount;
}

std::string FlatBonusModifier::getName() const {
    return "FlatBonus";
}

std::string FlatBonusModifier::getDescription() const {
    return "Menambah +" + std::to_string(bonusAmount) + " poin ke skor";
}

IModifier* FlatBonusModifier::clone() const {
    return new FlatBonusModifier(*this);
}
