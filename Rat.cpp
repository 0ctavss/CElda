#include "Rat.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

Rat::Rat(int x, int y, int range, int speed, int dmg)
    : posX(x), posY(y), visionRange(range), moveSpeed(speed), damage(dmg), isParalyzed(false) {
    std::srand(std::time(0)); // Inicializa la semilla para el movimiento aleatorio
}

void Rat::update(int playerX, int playerY) {
    if (isParalyzed) {
        // Si está paralizado, no se mueve
        return;
    }

    moveRandomly();

    if (detectSpectre(spectres)) {
        isParalyzed = true;
    }
    else {
        isParalyzed = false;
    }

    if (std::abs(playerX - posX) <= 1 && std::abs(playerY - posY) <= 1) {
        bitePlayer(playerX, playerY, playerHP);
    }
}

bool Rat::detectSpectre(const std::vector<Spectre>& spectres) {
    for (const auto& spectre : spectres) {
        int distance = std::sqrt(std::pow(spectre.getX() - posX, 2) + std::pow(spectre.getY() - posY, 2));
        if (distance <= visionRange) {
            return true;
        }
    }
    return false;
}

void Rat::moveRandomly() {
    int direction = std::rand() % 4;
    switch (direction) {
    case 0:
        posX += moveSpeed; // Moverse a la derecha
        break;
    case 1:
        posX -= moveSpeed; // Moverse a la izquierda
        break;
    case 2:
        posY += moveSpeed; // Moverse hacia arriba
        break;
    case 3:
        posY -= moveSpeed; // Moverse hacia abajo
        break;
    }
}

void Rat::bitePlayer(int playerX, int playerY, int& playerHP) {
    if (std::abs(playerX - posX) <= 1 && std::abs(playerY - posY) <= 1) {
        playerHP -= damage;
    }
}

