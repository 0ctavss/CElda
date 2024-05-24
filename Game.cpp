#include "Game.h"

Game::Game() : playerX(0), playerY(0), playerHP(5) {}

void Game::update() {
    for (auto& eye : spectralEyes) {
        eye.update(playerX, playerY);
    }

    for (auto& spectre : spectres) {
        spectre.update(playerX, playerY);
        if (spectre.isChasing) {
            spectre.alertNearbySpectres(spectres);
        }
    }

    for (auto& rat : rats) {
        rat.update(playerX, playerY);
    }

    for (auto& chocobo : chocobos) {
        chocobo.update(playerX, playerY, playerHP);
    }
}

void Game::addSpectralEye(int x, int y, int range) {
    spectralEyes.emplace_back(x, y, range, &spectres);
}

void Game::addSpectre(int x, int y, float speed) {
    spectres.emplace_back(x, y, speed);
}

void Game::addRat(int x, int y, int range, int speed, int damage) {
    rats.emplace_back(x, y, range, speed, damage);
}

void Game::addChocobo(int x, int y, int range, int speed, int damage) {
    chocobos.emplace_back(x, y, range, speed, damage);
}

// Método llamado por los Ojos Espectrales cuando detectan al jugador
void Game::alertSpectresNearby() {
    for (auto& spectre : spectres) {
        spectre.chasePlayer(playerX, playerY);
    }
}
