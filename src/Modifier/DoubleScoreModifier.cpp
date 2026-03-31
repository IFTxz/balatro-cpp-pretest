#include "DoubleScoreModifier.h"

int DoubleScoreModifier::apply(int currentScore) {
    return currentScore * 2;
}

std::string DoubleScoreModifier::getName() const {
    return "DoubleBoost";
}

std::string DoubleScoreModifier::getDescription() const {
    return "Menggandakan skor saat ini (x2)";
}

IModifier* DoubleScoreModifier::clone() const {
    return new DoubleScoreModifier(*this);
}
