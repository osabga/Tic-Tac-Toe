#include <iostream>
#include <string>
#include "gato.h"
#include <memory>
using namespace std;

// Declaracion de funciones.
void gameLoop(string, string);
void menu();


int main()
{
    menu();

    return 0;
}


//Funcion que muestra todo el menu.
void menu()
{
    string player1;
    string player2;
    string respuesta;
    string temporal;
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

    //Goto en caso de que se quiera volver a jugar
    jugar:

    gameLoop(player1, player2);
    //Goto en caso de que se de un input no vlaido para la pregunra, Volver a jugar?
    volverAPreguntar:
    cout << "Desea jugar otra vez?" << endl;
    cout << "1.- Si" << endl;
    cout << "2.- No" << endl;
    cin >> respuesta;

    if (respuesta == "1")
    {
        cin.clear();
        fflush(stdin);

        // Cambia el jugaro que empieza, el 2 ahora es el 1.
        temporal = player1;
        player1 = player2;
        player2 = temporal;
        goto jugar;
    }
    else if (respuesta == "2")
    {
        cout << "Gracias por jugar" << endl;
    }
    else
    {
        cout << "Opcion no valida" << endl;
        goto volverAPreguntar;
        cin.clear();
        fflush(stdin);
    }
}


// Funcion que contiene el loop del juego. 
// Se le pasa como parametro los nombres de los jugadores.
// Se crea un objeto de la clase gato y se llama a la funcion mostrarTablero.
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
