#include "SpectralEye.h"
#include <cmath>
#include <vector>
#include <iostream>

// Constructor
SpectralEye::SpectralEye(int x, int y, int range, std::vector<Spectre>* spectres)
    : posX(x), posY(y), visionRange(range), spectres(spectres) {}

// M�todo para actualizar el estado del Ojo Espectral
void SpectralEye::update(int playerX, int playerY) {
    if (detectPlayer(playerX, playerY)) {
        alertSpectres(playerX, playerY);
    }
}

// M�todo para detectar al jugador dentro del rango de visi�n
bool SpectralEye::detectPlayer(int playerX, int playerY) {
    int distance = std::sqrt(std::pow(playerX - posX, 2) + std::pow(playerY - posY, 2));
    return distance <= visionRange;
}

// M�todo para alertar a los espectros
void SpectralEye::alertSpectres(int playerX, int playerY) {
    std::cout << "Jugador detectado. �Alertando a los espectros!" << std::endl;
    alertSpectresNearby(*spectres, playerX, playerY);
}

// Funci�n que podr�a alertar a los espectros 
void alertSpectresNearby(std::vector<Spectre>& spectres, int playerX, int playerY) {
    for (auto& spectre : spectres) {
        spectre.chasePlayer(playerX, playerY);
    }
}

