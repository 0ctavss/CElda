#include "Game.h"

Game::Game() : playerX(0), playerY(0) {}

void Game::update() {
    for (auto& eye : spectralEyes) {
        eye.update(playerX, playerY);
    }
}

void Game::addSpectralEye(int x, int y, int range) {
    spectralEyes.emplace_back(x, y, range, &spectres);
}

void Game::addSpectre(int x, int y, float speed) {
    spectres.emplace_back(x, y, speed);
}

// Método llamado por los Ojos Espectrales cuando detectan al jugador
void Game::alertSpectresNearby() {
    for (auto& spectre : spectres) {
        spectre.chasePlayer(playerX, playerY);
    }
}
