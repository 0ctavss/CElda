#ifndef GAME_H
#define GAME_H

#include "SpectralEye.h"
#include "Spectre.h"
#include "Rat.h"
#include "Chocobo.h"
#include <vector>

class Game {
private:
    std::vector<SpectralEye> spectralEyes;
    std::vector<Spectre> spectres;
    std::vector<Rat> rats;
    std::vector<Chocobo> chocobos;
    int playerX;
    int playerY;
    int playerHP;

public:
    Game();
    void update();
    void addSpectralEye(int x, int y, int range);
    void addSpectre(int x, int y, float speed);
    void addRat(int x, int y, int range, int speed, int damage);
    void addChocobo(int x, int y, int range, int speed, int damage)
};

#endif // GAME_H
