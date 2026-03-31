#pragma once
#include "IModifier.h"

// Modifier C: mengkuadratkan skor (tapi dibatasi agar tidak terlalu besar)
// Ini adalah modifier yang ditambahkan untuk analisis A2 (Extensibility)
class SquareScoreModifier : public IModifier {
public:
    int apply(int currentScore) override;
    std::string getName() const override;
    std::string getDescription() const override;
    IModifier* clone() const override;
};
