#pragma once
#include "modifiers/IModifier.h"
#include "ModifierFactory.h"
#include <vector>

// ShopSystem: tempat pemain membeli modifier setelah setiap ronde
// Menggunakan ModifierFactory untuk membuat modifier yang dipilih
class ShopSystem {
public:
    // Tampilkan toko dan minta input pemain
    // Kembalikan modifier yang dipilih (nullptr jika skip)
    IModifier* openShop() const;

private:
    void displayShopMenu() const;
};
