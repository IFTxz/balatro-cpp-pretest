#pragma once
#include "ScoringSystem.h"
#include "ShopSystem.h"
#include "modifiers/IModifier.h"
#include <vector>

// RunSession: Controller utama yang mengatur loop game
// Mengelola state: ronde saat ini, modifier aktif, skor total
class RunSession {
private:
    int currentRound;
    int totalRounds;
    int totalScore;
    std::vector<IModifier*> activeModifiers;
    ScoringSystem scorer;
    ShopSystem shop;

    // Generate tangan kartu acak (5 kartu dengan nilai 1-13)
    std::vector<int> dealHand() const;

    // Tampilkan kartu di tangan
    void displayHand(const std::vector<int>& hand) const;

    // Tampilkan modifier yang sedang aktif
    void displayActiveModifiers() const;

    // Tampilkan header satu ronde
    void displayRoundHeader(int round) const;

    // Mainkan satu ronde
    void playRound(int round);

public:
    RunSession(int rounds = 3);
    ~RunSession();

    // Mulai game
    void start();
};
