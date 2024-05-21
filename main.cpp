#include "Spectre.h"
#include "SpectralEye.h"
#include "Rat.h"
#include "Chocobo.h"
#include "Game.h"

int main() {
    Game game;

    // Agregar espectros y ojos espectrales al juego
    game.addSpectralEye(5, 5, 3);
    game.addSpectre(10, 10, 1.0f);
    game.addSpectre(15, 15, 1.5f);

    // Bucle principal del juego
    while (true) {
        // Actualizar el juego 
        game.update();

        //Lgica adicional del juego 
    }

    return 0;
}

