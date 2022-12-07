#ifndef _GATO_H_
#define _GATO_H_

#include <iostream>

#include <string>

class gato
{
private:
    std::string jugador1; // Jugador que se mueve con las X
    std::string jugador2; // Jugador que se mueve con las O
    int turno{1};
    bool juego = true;

    std::string mostrar[9];
    void revisaGanador();
    void ganador(std::string ganador);
    bool validacion(std::string seleccion);

public:
    bool fin();
    void mostrarTablero();
    gato(std::string jugador1, std::string jugador2);
    
    void jugada();
};

#endif