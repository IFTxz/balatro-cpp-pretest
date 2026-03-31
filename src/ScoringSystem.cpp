#include "ScoringSystem.h"
#include <numeric>

// Base score = jumlah semua nilai kartu di tangan
int ScoringSystem::calculateBase(const std::vector<int>& hand) const {
    return std::accumulate(hand.begin(), hand.end(), 0);
}

// Decorator-like chain: setiap modifier diterapkan secara berurutan
// Contoh: baseScore=100, modifier=[double, flat+50]
//   -> setelah double: 200
//   -> setelah flat:   250
// Jika dibalik [flat, double]:
//   -> setelah flat:   150
//   -> setelah double: 300
// => Urutan SANGAT berpengaruh!
int ScoringSystem::applyModifiers(int baseScore, const std::vector<IModifier*>& modifiers) const {
    int score = baseScore;
    for (IModifier* modifier : modifiers) {
        score = modifier->apply(score);
    }
    return score;
}

int ScoringSystem::calculateFinal(const std::vector<int>& hand, const std::vector<IModifier*>& modifiers) const {
    int base = calculateBase(hand);
    return applyModifiers(base, modifiers);
}
