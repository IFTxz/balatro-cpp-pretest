# Design Pattern Analysis
**Card-Run Game — Pretest Design Pattern**

---

## PART A — Creational Pattern Analysis

### A1 — Factory
Semua objek modifier dibuat di `ModifierFactory::create()` dalam file `src/ModifierFactory.cpp`.

Class `ModifierFactory` menerima parameter string (tipe modifier) dan mengembalikan pointer ke `IModifier`. Seluruh kode lain (seperti `ShopSystem.cpp`) memanggil `ModifierFactory::create()` tanpa perlu tahu class konkret yang dipakai.

**Mengapa centralisasi bermanfaat?**
Karena jika ingin menambah modifier baru, hanya `ModifierFactory.cpp` yang perlu diubah. Kode di `ShopSystem`, `RunSession`, dan `ScoringSystem` tidak perlu disentuh. Ini menerapkan prinsip **Open/Closed Principle**.

---

### A2 — Extensibility: Menambahkan SquareScoreModifier
Langkah yang dilakukan:
1. Membuat `src/modifiers/SquareScoreModifier.h` — deklarasi class
2. Membuat `src/modifiers/SquareScoreModifier.cpp` — implementasi `apply()`, `getName()`, dll
3. Menambahkan satu baris di `ModifierFactory.cpp`: `if (type == "square") return new SquareScoreModifier();`
4. Menambahkan `"square"` ke array di `getAvailableTypes()`

**File yang berubah:** `SquareScoreModifier.h` (baru), `SquareScoreModifier.cpp` (baru), `ModifierFactory.cpp` (2 baris).

Desain ini sangat mudah di-extend karena Factory mengisolasi pembuatan objek.

---

### A3 — Factory Method (Conceptual)
Jika ada beberapa tipe toko (ShopNormal, ShopPremium, ShopRandom), Factory Method membantu dengan cara:

```cpp
class IShopFactory {
public:
    virtual ShopSystem* createShop() = 0;
};

class NormalShopFactory : public IShopFactory {
public:
    ShopSystem* createShop() override { return new ShopNormal(); }
};
```

Dengan ini, `RunSession` bisa menerima `IShopFactory*` tanpa tahu tipe toko konkret.

---

### A4 — Prototype (Conceptual)
Method `clone()` sudah diimplementasikan di setiap modifier (lihat `DoubleScoreModifier.cpp`).

`Clone()` berguna ketika pemain ingin menduplikasi modifier yang sudah ada di tangan, misalnya efek "copy modifier terakhir". Daripada membuat ulang lewat factory, kita panggil `modifier->clone()` yang membuat salinan identik.

Implementasi ada di semua class modifier (contoh: `DoubleScoreModifier::clone()` di `src/modifiers/DoubleScoreModifier.cpp`).

---

### A5 — Singleton (Conceptual)
Program ini tidak menggunakan global object eksplisit. Namun `ScoringSystem` dan `ShopSystem` berpotensi dijadikan Singleton karena tidak menyimpan state — hanya berisi method.

**Keuntungan Singleton:** Satu instance di seluruh program, hemat memori.  
**Risiko:** Sulit di-test (tidak bisa di-mock), membuat ketergantungan tersembunyi antar class.

---

## PART B — Structural Pattern Analysis

### B1 — Decorator Concept
Modifier chain di `ScoringSystem::applyModifiers()` (`src/ScoringSystem.cpp`) berperilaku seperti Decorator pattern.

Yang didekorasi adalah **nilai skor (integer)**. Setiap modifier membungkus nilai tersebut dan mengubahnya, seperti decorator membungkus objek asli:
```cpp
for (IModifier* modifier : modifiers) {
    score = modifier->apply(score); // setiap lapisan menambah perilaku
}
```

---

### B2 — Modifier Order
Ya, urutan modifier sangat berpengaruh. Contoh dari `ScoringSystem.cpp`:

- Base score = 100
- Modifier: `[DoubleBoost, FlatBonus+50]`
  - Setelah Double: 200 → Setelah Flat: **250**
- Modifier: `[FlatBonus+50, DoubleBoost]`
  - Setelah Flat: 150 → Setelah Double: **300**

Output berbeda 50 poin hanya karena urutan berbeda.

---

### B3 — Composite (Conceptual)
Modifier group bisa diimplementasikan dengan class `CompositeModifier` yang berisi kumpulan modifier:

```cpp
class CompositeModifier : public IModifier {
    vector<IModifier*> children;
public:
    int apply(int score) override {
        for (auto m : children) score = m->apply(score);
        return score;
    }
};
```

Ini memungkinkan "paket modifier" diperlakukan seperti satu modifier tunggal.

---

### B4 — Adapter (Conceptual)
Misalnya ada library scoring eksternal dengan interface berbeda:
```cpp
class ExternalScorer { public: float computeScore(float val); };
```

Kita buat Adapter:
```cpp
class ExternalScorerAdapter : public IModifier {
    ExternalScorer* ext;
public:
    int apply(int score) override {
        return (int)ext->computeScore((float)score);
    }
};
```

Sehingga library eksternal bisa dipakai tanpa mengubah kode yang sudah ada.

---

### B5 — Facade (Conceptual)
```cpp
class GameFacade {
    RunSession* session;
    ScoringSystem* scorer;
    ShopSystem* shop;
public:
    void startGame();           // mulai run session
    int playHand();             // deal + hitung skor
    void openShop();            // buka toko
    int getTotalScore() const;  // ambil skor total
};
```

`GameFacade` menyembunyikan kompleksitas interaksi antar subsystem dari `main.cpp`.

---

## PART C — Behavioral Pattern Analysis

### C1 — Strategy
Logika scoring ada di `ScoringSystem::calculateBase()` dan `applyModifiers()` di `src/ScoringSystem.cpp`.

Untuk mendukung multiple scoring rule (misal: mode normal vs mode hardcore):
```cpp
class IScoringStrategy {
public:
    virtual int calculate(const vector<int>& hand) = 0;
};
class NormalScoring : public IScoringStrategy { ... };
class HardcoreScoring : public IScoringStrategy { ... };
```

`RunSession` bisa menerima `IScoringStrategy*` yang bisa diganti saat runtime.

---

### C2 — Observer (Conceptual)
Event yang ada di sistem: `onRoundEnd`, `onModifierApplied`, `onScoreCalculated`.

Dengan Observer, sistem lain (misal: achievement tracker, logger) bisa subscribe ke event ini tanpa `RunSession` perlu tahu siapa yang mendengarkan:
```cpp
class IGameObserver {
public:
    virtual void onRoundEnd(int score) = 0;
    virtual void onModifierApplied(string name, int before, int after) = 0;
};
```

---

### C3 — Command (Conceptual)
Aksi yang bisa direpresentasikan sebagai Command: `PlayHandCommand`, `BuyModifierCommand`, `SkipShopCommand`.

Keuntungan: bisa di-undo, di-queue, atau di-log untuk replay.

```cpp
class ICommand { public: virtual void execute() = 0; virtual void undo() = 0; };
class BuyModifierCommand : public ICommand {
    string modifierType;
    vector<IModifier*>& activeList;
public:
    void execute() override { activeList.push_back(ModifierFactory::create(modifierType)); }
    void undo() override { delete activeList.back(); activeList.pop_back(); }
};
```

---

### C4 — State (Conceptual)
Run phase bisa diorganisasi dengan State pattern:

```cpp
class IRunState { public: virtual void handle(RunSession* ctx) = 0; };
class DealState    : public IRunState { ... }; // bagikan kartu
class ScoringState : public IRunState { ... }; // hitung skor
class ShopState    : public IRunState { ... }; // buka toko
class EndState     : public IRunState { ... }; // akhiri run
```

`RunSession` menyimpan `IRunState* currentState` dan memanggil `currentState->handle(this)` setiap iterasi, sehingga transisi antar fase lebih terstruktur.
