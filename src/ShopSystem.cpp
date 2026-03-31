#include "ShopSystem.h"
#include <iostream>
#include <vector>
#include <string>

void ShopSystem::displayShopMenu() const {
    std::vector<std::string> types = ModifierFactory::getAvailableTypes();
    std::cout << "\n \n";
    std::cout << "  ||         ~ TOKO BOOST ~      ||\n";
    std::cout << "  \n";

    // Buat objek sementara hanya untuk tampilkan deskripsi
    for (int i = 0; i < (int)types.size(); i++) {
        IModifier* temp = ModifierFactory::create(types[i]);
        if (temp) {
            std::cout << "  [" << (i + 1) << "] " << temp->getName()
                      << " - " << temp->getDescription() << "\n";
            delete temp;
        }
    }
    std::cout << "  [0] Lewati (Skip)\n";
    std::cout << "  Pilihan kamu: ";
}

IModifier* ShopSystem::openShop() const {
    displayShopMenu();

    int choice;
    std::cin >> choice;

    std::vector<std::string> types = ModifierFactory::getAvailableTypes();

    if (choice <= 0 || choice > (int)types.size()) {
        std::cout << "  >> Kamu melewati toko.\n";
        return nullptr;
    }

    IModifier* modifier = ModifierFactory::create(types[choice - 1]);
    if (modifier) {
        std::cout << "  >> Kamu membeli: " << modifier->getName() << "!\n";
    }
    return modifier;
}
