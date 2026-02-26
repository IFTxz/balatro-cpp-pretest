#include "RunSession.h"

// Entry point program
// Cukup buat RunSession dan panggil start()
int main() {
    RunSession session(3); // 3 ronde
    session.start();
    return 0;
}
