#ifndef RAT_H
#define RAT_H

#include "Spectre.h"
#include <vector>

class Rat {
private:
    int posX;
    int posY;
    int visionRange;
    int moveSpeed;
    int damage;
    bool isParalyzed;

public:
    Rat(int x, int y, int range, int speed, int dmg);
    void update(int playerX, int playerY);
    bool detectSpectre(const std::vector<Spectre>& spectres);
    void moveRandomly();
    void bitePlayer(int playerX, int playerY, int& playerHP);

    int getX() const { return posX; }
    int getY() const { return posY; }
};

#endif // RAT_H


