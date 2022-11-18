#include <iostream>
#include "gato.h"

void gameLoop();

int main()
{
    gameLoop();
}

void gameLoop()
{
    gato Juego{"Oskar", "Oskar2"};
    Juego.mostrarTablero();
    // Game loop
    while (Juego.fin())
    {
        Juego.jugada();
    }
}