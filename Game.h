#ifndef GAME_H
#define GAME_H

#include "SpectralEye.h"
#include "Spectre.h"
#include <vector>

class Game {
private:
    std::vector<SpectralEye> spectralEyes;
    std::vector<Spectre> spectres;
    int playerX;
    int playerY;

public:
    Game();
    void update();
    void addSpectralEye(int x, int y, int range);
    void addSpectre(int x, int y, float speed);
};

#endif // GAME_H
