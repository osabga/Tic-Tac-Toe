#include <iostream>
#include <string>
using namespace std;

// Falta lo del bot y empate

void showGrid(char positions[])
{
    cout << "       |       |       " << endl;
    cout << "   " << positions[0] << "   |   " << positions[1] << "   |   " << positions[2] << "   " << endl;
    cout << "_______|_______|_______" << endl;
    cout << "       |       |         " << endl;
    cout << "   " << positions[3] << "   |   " << positions[4] << "   |   " << positions[5] << "   " << endl;
    cout << "_______|_______|_______" << endl;
    cout << "       |       |         " << endl;
    cout << "   " << positions[6] << "   |   " << positions[7] << "   |   " << positions[8] << "   " << endl;
    cout << "       |       |       " << endl;
}

int askPosition(char positions[], bool player)
{
    showGrid(positions);
    string res;

    cout << "Player " << player + 1 << ": Position to play? (1-9)" << endl;
    cin >> res;

    try
    {

        if (stoi(res) < 1 || stoi(res) > 9)
        {
            throw 505;
        }

        if (positions[stoi(res) - 1] == 'O' ||
            positions[stoi(res) - 1] == 'X')
        {
            cout << "Invalid response" << endl;
            return askPosition(positions, player);
        }
        else
        {
            positions[stoi(res) - 1] = *(player ? "X" : "O");
            return stoi(res) - 1;
        }
    }
    catch (...)
    {
        cout << "Invalid response" << endl;
        return askPosition(positions, player);
    }
}

bool checkWin(char positions[], int lastPosition, bool player)
{
    int combinations[9][4][2] = {
        {{1, 2}, {4, 8}, {3, 6}},
        {{0, 2}, {4, 7}},
        {{0, 1}, {5, 8}, {4, 6}},
        {{4, 5}, {0, 6}},
        {{3, 5}, {1, 7}, {0, 8}, {2, 6}},
        {{2, 8}, {3, 4}},
        {{0, 3}, {7, 8}, {2, 4}},
        {{1, 4}, {6, 8}},
        {{2, 5}, {6, 7}, {0, 4}}};

    int posibilities = lastPosition == 4 ? 4 : 3 - lastPosition % 2;

    for (int i = 0; i < posibilities; i++)
    {
        int total = 0;
        for (int j = 0; j < 2; j++)
        {
            if (positions[combinations[lastPosition][i][j]] == (player ? 'X' : 'O'))
            {
                total++;
            }
            if (total == 2)
            {
                return true;
            }
        }
    }

    return false;
}

// Aun no se como hacerle para implemetnar este pedo
/*
void onePlayer(char positions[])
{
    bool win = false;
    bool player = false;

    while (!win)
    {
        int lastPosition = player ? bestMove(positions) : askPosition(positions, player);
        win = checkWin(positions, lastPosition, player);
    }
}
*/

// Regresa True si ya no hay posiciones disponibles para jugar, por ende si hay empate, false si no
bool TerminaJuego(char positions[])
{
    for (int i = 0; i < 9; i++)
    {
        if (positions[i] == 'X' || positions[i] == 'O')
        {
            return false;
        }
    }
    return true;
}

int evaluation(char positions[])
{
    // Revisamos las posibles convinaciones de victoria
    //  -10 Si gana el jugador 1
    //  +10 Si gana el jugador 2
    //  +0 si no gana nadie, empate o el juego aun no termina
    if (positions[0] == positions[1] && positions[1] == positions[2])
    {
        cout << "Gano " << positions[0];
        if (positions[1] == 'O')
        {
            return -10;
        }
        else
        {
            return 10;
        }
    }
    else if (positions[3] == positions[4] && positions[4] == positions[5])
    {
        cout << "Gano " << positions[3];
        if (positions[3] == 'O')
        {
            return -10;
        }
        else
        {
            return 10;
        }
    }
    else if (positions[6] == positions[7] && positions[7] == positions[8])
    {
        cout << "Gano " << positions[6];
        if (positions[6] == 'O')
        {
            return -10;
        }
        else
        {
            return 10;
        }
    }
    else if (positions[0] == positions[4] && positions[4] == positions[8])
    {
        cout << "Gano " << positions[0];
        if (positions[0] == 'O')
        {
            return -10;
        }
        else
        {
            return 10;
        }
    }
    else if (positions[6] == positions[4] && positions[4] == positions[2])
    {
        cout << "Gano " << positions[6];
        if (positions[6] == 'O')
        {
            return -10;
        }
        else
        {
            return 10;
        }
    }
    else if (positions[0] == positions[3] && positions[3] == positions[6])
    {
        cout << "Gano " << positions[6];
        if (positions[6] == 'O')
        {
            return -10;
        }
        else
        {
            return 10;
        }
    }
    else if (positions[1] == positions[4] && positions[4] == positions[7])
    {
        cout << "Gano " << positions[1];
        if (positions[1] == 'O')
        {
            return -10;
        }
        else
        {
            return 10;
        }
    }
    else if (positions[2] == positions[5] && positions[5] == positions[8])
    {
        cout << "Gano " << positions[2];
        if (positions[2] == 'O')
        {
            return -10;
        }
        else
        {
            return 10;
        }
    }
    else
    {
        //cout << "No ha ganado Nadie" << endl;
        return 0;
    }
    
}

int minimax(char positions[], int depth, bool player)
{

    int score = evaluation(positions);
    // Si Gana el Bot
    if (score == 10)
    {
        return score;
    }
    // Si gana el Humano
    if (score == -10)
    {
        return score;
    }
    // Empate
    if (TerminaJuego(positions) == true)
    {
        return 0;
    }
    // si player es true, es el jugador 2 por ende el bot
    if (player)
    {

        int best = -1000;
        for (int i = 0; i < 9; i++)
        {
            if (positions[i] != 'X' || positions[i] != 'O')
            {
                positions[i] = 'X';

                best = max(best, minimax(positions, depth + 1, !player));

                positions[i] = i + 49;
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i < 9; i++)
        {
            if (positions[i] != 'X' || positions[i] != 'O')
            {
                positions[i] = 'O';

                best = max(best, minimax(positions, depth + 1, !player));

                positions[i] = i + 49;
            }
        }
        return best;
    }
}

void bestMove(char positions[])
{
    int bestVal = -1000;
    int OptiMove;
    for (int i = 0; i < 9; i++)
    {
        if (positions[i] != 'X' || positions[i] != 'O')
        {
            positions[i] = 'X';

            int ValMove = minimax(positions, 0 + 1, true);

            positions[i] = i + 49;

            if (ValMove > bestVal)
            {
                OptiMove = 1 + i;
                bestVal = ValMove;
            }
        }
    }
    cout << "El mejor movimiento para el bot es el indice " << OptiMove << endl;
}

void twoPlayers(char positions[])
{
    bool win = false, player = false;
    int plays = 0;

    while (!win && plays < 9)
    {

        if (player)
        {
            bestMove(positions);
        }


        int lastPosition = askPosition(positions, player);
        win = checkWin(positions, lastPosition, player);
        player = !player;
        plays++;
    }

    if (win)
    {
        showGrid(positions);
        player = !player;

        cout << endl
             << "Player " << player + 1 << " won!" << endl;
    }
    else
    {
        cout << endl
             << "It was a tie!" << endl;
    }
    cout << "Thanks for playing!" << endl;
}

void playerNumbers()
{
    string res;

    char positions[9];

    for (int i = 0; i < 9; i++)
    {
        positions[i] = i + 49;
    }

    cout << "How many players? (1/2)" << endl;
    cin >> res;

    if (res == "1")
    {
        // onePlayer(positions);
    }
    else if (res == "2")
    {
        twoPlayers(positions);
    }
    else if (res == "exit")
    {
        cout << "Thanks for playing!" << endl;
    }
    else
    {
        cout << "Invalid response" << endl
             << endl;
        playerNumbers();
    }
}

int main()
{
    cout << "---------------------------------------------" << endl;
    cout << "TIC TAC TOE" << endl;
    cout << "----------------------------------------------" << endl;
    cout << endl;

    playerNumbers();

    return 0;
}
