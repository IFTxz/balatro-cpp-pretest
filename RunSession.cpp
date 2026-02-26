#include "RunSession.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

RunSession::RunSession(int rounds)
    : currentRound(1), totalRounds(rounds), totalScore(0) {
    srand((unsigned int)time(nullptr));
}

RunSession::~RunSession() {
    for (IModifier* m : activeModifiers) delete m;
    activeModifiers.clear();
}

std::vector<int> RunSession::dealHand() const {
    std::vector<int> hand;
    for (int i = 0; i < 5; i++) {
        hand.push_back((rand() % 13) + 1); // nilai 1-13
    }
    return hand;
}

void RunSession::displayHand(const std::vector<int>& hand) const {
    std::cout << "  Kartu kamu: [ ";
    for (int val : hand) {
        if      (val == 1)  std::cout << "A ";
        else if (val == 11) std::cout << "J ";
        else if (val == 12) std::cout << "Q ";
        else if (val == 13) std::cout << "K ";
        else                std::cout << val << " ";
    }
    std::cout << "]\n";
}

void RunSession::displayActiveModifiers() const {
    if (activeModifiers.empty()) {
        std::cout << "  Modifier aktif: (tidak ada)\n";
        return;
    }
    std::cout << "  Modifier aktif: ";
    for (int i = 0; i < (int)activeModifiers.size(); i++) {
        if (i > 0) std::cout << " -> ";
        std::cout << "[" << activeModifiers[i]->getName() << "]";
    }
    std::cout << "\n";
}

void RunSession::displayRoundHeader(int round) const {
    std::cout << "\n";
    std::cout << "  ==========================================\n";
    std::cout << "        RONDE " << round << " dari " << totalRounds << "\n";
    std::cout << "  ==========================================\n";
}

void RunSession::playRound(int round) {
    displayRoundHeader(round);

    // Deal kartu
    std::vector<int> hand = dealHand();
    displayHand(hand);
    displayActiveModifiers();

    // Hitung base score
    int baseScore = scorer.calculateBase(hand);
    std::cout << "\n  >> Base Score    : " << baseScore << "\n";

    // Terapkan modifier satu per satu dan tampilkan prosesnya
    int score = baseScore;
    if (!activeModifiers.empty()) {
        std::cout << "  >> Applying modifiers:\n";
        for (IModifier* mod : activeModifiers) {
            int before = score;
            score = mod->apply(score);
            std::cout << "     [" << mod->getName() << "] : "
                      << before << " -> " << score << "\n";
        }
    }

    std::cout << "  >> Final Score   : " << score << "\n";
    totalScore += score;
    std::cout << "  >> Total Score   : " << totalScore << "\n";

    // Buka toko (kecuali ronde terakhir)
    if (round < totalRounds) {
        std::cout << "\n  Mau mampir ke toko dulu? (y/n): ";
        char answer;
        std::cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            IModifier* newMod = shop.openShop();
            if (newMod) {
                activeModifiers.push_back(newMod);
            }
        }
    }
}

void RunSession::start() {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════╗\n";
    std::cout << "  ║   CARD-RUN GAME  |  Design Pattern   ║\n";
    std::cout << "  ╚══════════════════════════════════════╝\n";
    std::cout << "  Selamat datang! Run " << totalRounds << " ronde akan dimulai.\n";
    std::cout << "  Tekan Enter untuk mulai...";
    std::cin.ignore();
    std::cin.get();

    for (int i = 1; i <= totalRounds; i++) {
        playRound(i);
    }

    // End Run summary
    std::cout << "\n";
    std::cout << "  ==========================================\n";
    std::cout << "              ~~  END RUN  ~~\n";
    std::cout << "  ==========================================\n";
    std::cout << "  Total Ronde    : " << totalRounds << "\n";
    std::cout << "  Total Score    : " << totalScore << "\n";
    std::cout << "  Modifier Aktif : " << activeModifiers.size() << " buah\n";
    if (!activeModifiers.empty()) {
        std::cout << "  Daftar Modifier: ";
        for (auto m : activeModifiers) std::cout << "[" << m->getName() << "] ";
        std::cout << "\n";
    }
    std::cout << "\n  Terima kasih sudah bermain!\n\n";
}
