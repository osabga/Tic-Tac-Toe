#include <iostream>
#include <string>
#include "gato.h"

using namespace std;

// Declaracion de funciones.
void gameLoop(string, string);
void menu();

int main()
{
    menu();

    return 0;
}

void menu()
{
    string player1;
    string player2;
    cout << "---------------------------------------------" << endl;
    cout << "Buenos dias al juego del gato" << endl;
    cout << "----------------------------------------------" << endl;
    cout << endl;
    cout << "Como se llama el jugador 1" << endl;
    cin >> player1;
    cout << endl;
    cout << "Como se llama el jugador 2 " << endl;
    cin >> player2;

    cin.clear();
    fflush(stdin);

    gameLoop(player1, player2);
}

//Falta hacer opcion pra jugar otra vez y cambiar quien empieza
// Falta marcar cuando termina el juego y que salga del GameLoop;
void gameLoop(string Jugador1, string jugador2)
{
    gato Juego{Jugador1, jugador2};
    Juego.mostrarTablero();
    // Game loop
    while (Juego.fin())
    {
        Juego.jugada();
    }
}
