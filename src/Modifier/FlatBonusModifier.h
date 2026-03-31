#pragma once
#include "IModifier.h"

// Modifier B: menambah nilai flat tetap ke skor
class FlatBonusModifier : public IModifier {
private:
    int bonusAmount;
public:
    FlatBonusModifier(int amount = 50);
    int apply(int currentScore) override;
    std::string getName() const override;
    std::string getDescription() const override;
    IModifier* clone() const override;
};
