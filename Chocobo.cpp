#include "Chocobo.h"
#include <cstdlib>
#include <ctime>

Chocobo::Chocobo(int x, int y, int range, int speed, int dmg)
    : posX(x), posY(y), visionRange(range), moveSpeed(speed), damage(dmg) {
    std::srand(std::time(0)); // Inicializa la semilla para el movimiento aleatorio
}

void Chocobo::update(int playerX, int playerY, int& playerHP) {
    if (hasLineOfSight(playerX, playerY)) {
        moveTowardsPlayer(playerX, playerY);
        if (std::abs(playerX - posX) <= 1 && std::abs(playerY - posY) <= 1) {
            attackPlayer(playerX, playerY, playerHP);
        }
    }
    else {
        // Movimiento aleatorio o patrullaje si no ve al jugador
        int direction = std::rand() % 4;
        switch (direction) {
        case 0: posX += moveSpeed; break; // Moverse a la derecha
        case 1: posX -= moveSpeed; break; // Moverse a la izquierda
        case 2: posY += moveSpeed; break; // Moverse hacia arriba
        case 3: posY -= moveSpeed; break; // Moverse hacia abajo
        }
    }
}

bool Chocobo::hasLineOfSight(int playerX, int playerY) {
    int dx = playerX - posX;
    int dy = playerY - posY;
    if (std::sqrt(dx * dx + dy * dy) > visionRange) {
        return false;
    }

    int absDx = std::abs(dx);
    int absDy = std::abs(dy);
    int sx = (dx > 0) ? 1 : -1;
    int sy = (dy > 0) ? 1 : -1;
    int err = absDx - absDy;

    int x = posX;
    int y = posY;

    while (x != playerX || y != playerY) {
        int e2 = err * 2;
        if (e2 > -absDy) {
            err -= absDy;
            x += sx;
        }
        if (e2 < absDx) {
            err += absDx;
            y += sy;
        }
        // Agregar verificación para obstáculos en el mapa
    }

    return true;
}

void Chocobo::moveTowardsPlayer(int playerX, int playerY) {
    if (playerX > posX) posX += moveSpeed;
    if (playerX < posX) posX -= moveSpeed;
    if (playerY > posY) posY += moveSpeed;
    if (playerY < posY) posY -= moveSpeed;
}

void Chocobo::attackPlayer(int playerX, int playerY, int& playerHP) {
    if (std::abs(playerX - posX) <= 1 && std::abs(playerY - posY) <= 1) {
        playerHP -= damage;
    }
}
