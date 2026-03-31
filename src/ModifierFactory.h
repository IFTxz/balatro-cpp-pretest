#pragma once
#include "modifiers/IModifier.h"
#include <string>
#include <vector>

// Factory Pattern: memusatkan pembuatan semua objek modifier
// Manfaat: kode lain tidak perlu tahu class konkret modifier
class ModifierFactory {
public:
    // Membuat modifier berdasarkan nama tipe
    static IModifier* create(const std::string& type);

    // Mendapatkan daftar semua tipe modifier yang tersedia
    static std::vector<std::string> getAvailableTypes();
};
