#include "ModifierFactory.h"
#include "modifiers/DoubleScoreModifier.h"
#include "modifiers/FlatBonusModifier.h"
#include "modifiers/SquareScoreModifier.h"
#include "modifiers/RandomBonusModifier.h"

// Factory Pattern: satu tempat untuk membuat semua modifier
// Untuk menambah modifier baru, cukup tambahkan kondisi di sini
// tanpa mengubah kode di tempat lain (Open/Closed Principle)
IModifier* ModifierFactory::create(const std::string& type) {
    if (type == "double")  return new DoubleScoreModifier();
    if (type == "flat")    return new FlatBonusModifier(50);
    if (type == "square")  return new SquareScoreModifier();
    if (type == "random")  return new RandomBonusModifier();
    return nullptr;
}

std::vector<std::string> ModifierFactory::getAvailableTypes() {
    return { "double", "flat", "square", "random" };
}
