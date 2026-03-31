#pragma once
#include "IModifier.h"

// Modifier A: menggandakan skor saat ini
class DoubleScoreModifier : public IModifier {
public:
    int apply(int currentScore) override;
    std::string getName() const override;
    std::string getDescription() const override;
    IModifier* clone() const override;
};
