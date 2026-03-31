#pragma once
#include "IModifier.h"

// Modifier D: menambah bonus acak antara 10-100
class RandomBonusModifier : public IModifier {
public:
    int apply(int currentScore) override;
    std::string getName() const override;
    std::string getDescription() const override;
    IModifier* clone() const override;
};
