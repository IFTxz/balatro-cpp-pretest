#pragma once
#include "modifiers/IModifier.h"
#include <vector>

// Strategy Pattern: logika perhitungan skor dipisahkan ke class ini
// Jika ingin scoring rule berbeda (misal: mode hardcore),
// bisa buat subclass baru tanpa ubah kode lain
class ScoringSystem {
public:
    // Hitung base score dari nilai kartu di tangan
    int calculateBase(const std::vector<int>& hand) const;

    // Terapkan semua modifier secara berantai (Decorator-like chain)
    // Urutan modifier BERPENGARUH terhadap hasil akhir
    int applyModifiers(int baseScore, const std::vector<IModifier*>& modifiers) const;

    // Hitung total skor akhir
    int calculateFinal(const std::vector<int>& hand, const std::vector<IModifier*>& modifiers) const;
};
