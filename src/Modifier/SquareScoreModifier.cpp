#include "SquareScoreModifier.h"

int SquareScoreModifier::apply(int currentScore) {
    // Dibatasi maksimal 9999 agar tidak overflow
    int result = currentScore * currentScore;
    return (result > 9999) ? 9999 : result;
}

std::string SquareScoreModifier::getName() const {
    return "SquareBoost";
}

std::string SquareScoreModifier::getDescription() const {
    return "Mengkuadratkan skor saat ini (maks 9999)";
}

IModifier* SquareScoreModifier::clone() const {
    return new SquareScoreModifier(*this);
}
