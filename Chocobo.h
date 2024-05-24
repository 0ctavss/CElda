#ifndef CHOCOBO_H
#define CHOCOBO_H

#include <vector>
#include <cmath>

class Chocobo {
private:
    int posX;
    int posY;
    int visionRange;
    int moveSpeed;
    int damage;

public:
    Chocobo(int x, int y, int range, int speed, int dmg);
    void update(int playerX, int playerY, int& playerHP);
    bool hasLineOfSight(int playerX, int playerY);
    void moveTowardsPlayer(int playerX, int playerY);
    void attackPlayer(int playerX, int playerY, int& playerHP);

    int getX() const { return posX; }
    int getY() const { return posY; }
};

#endif // CHOCOBO_H


