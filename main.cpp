#include <iostream>
#include <climits>
#include <string>
using namespace std;

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

        if (positions[stoi(res) - 1] == 'O' || positions[stoi(res) - 1] == 'X')
        {
            cout << "Invalid response" << endl;
            return askPosition(positions, player);
        }
        else
        {
            positions[stoi(res) - 1] = (player ? 'X' : 'O');
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
        // cout << "Gano " << positions[0];
        if (positions[1] == 'O')
            return (-10);
        else
            return 10;
    }
    else if (positions[3] == positions[4] && positions[4] == positions[5])
    {
        // cout << "Gano " << positions[3];
        if (positions[3] == 'O')
            return -10;
        else
            return 10;
    }
    else if (positions[6] == positions[7] && positions[7] == positions[8])
    {
        // cout << "Gano " << positions[6];
        if (positions[6] == 'O')
            return -10;
        else
            return 10;
    }
    else if (positions[0] == positions[4] && positions[4] == positions[8])
    {
        // cout << "Gano " << positions[0];
        if (positions[0] == 'O')
            return -10;
        else
            return 10;
    }
    else if (positions[6] == positions[4] && positions[4] == positions[2])
    {
        // cout << "Gano " << positions[6];
        if (positions[6] == 'O')
            return -10;
        else
            return 10;
    }
    else if (positions[0] == positions[3] && positions[3] == positions[6])
    {
        // cout << "Gano " << positions[6];
        if (positions[0] == 'O')
            return -10;
        else
            return 10;
    }
    else if (positions[1] == positions[4] && positions[4] == positions[7])
    {
        // cout << "Gano " << positions[1];
        if (positions[1] == 'O')
            return -10;
        else
            return 10;
    }
    else if (positions[2] == positions[5] && positions[5] == positions[8])
    {
        // cout << "Gano " << positions[2];
        if (positions[2] == 'O')
            return -10;
        else
            return 10;
    }
    else
    {
        // cout << "No ha ganado Nadie" << endl;
        return 0;
    }
}

int minimax(char positions[], int depth, bool player)
{
    int score = evaluation(positions);
    // Si Gana el Bot/Humano
    if (score != 0)
        return score;
    // Empate
    if (TerminaJuego(positions))
        return 0;
    // si player es true, es el jugador 2 por ende el bot
    if (player)
    {
        int maximum = INT_MIN;
        for (int i = 0; i < 9; i++)
        {
            if (positions[i] != 'X' && positions[i] != 'O')
            {
                positions[i] = 'X';
                int mx = minimax(positions, depth + 1, !player);
                maximum = max(maximum, mx);
                positions[i] = i + 49;
            }
        }
        return maximum - depth;
    }
    else
    {
        int minimum = INT_MAX;
        for (int i = 0; i < 9; i++)
        {
            if (positions[i] != 'X' && positions[i] != 'O')
            {
                positions[i] = 'O';
                int mm = minimax(positions, depth + 1, !player);
                minimum = min(minimum, mm);
                positions[i] = i + 49;
            }
        }
        return minimum - depth;
    }
}

int bestMove(char positions[])
{
    int bestVal = INT_MIN;
    int OptiMove;
    for (int i = 0; i < 9; i++)
    {
        if (positions[i] != 'X' && positions[i] != 'O')
        {
            positions[i] = 'X';

            int ValMove = minimax(positions, 0, false);
            positions[i] = i + 49;

            if (ValMove > bestVal)
            {
                OptiMove = i;
                bestVal = ValMove;
            }
        }
    }
    positions[OptiMove] = 'X';
    return OptiMove;
}

// Falta funcionar para cuando el humano empiece

void onePlayer(char positions[])
{
    bool win = false, player = false;
    int plays = 0, lastPosition;
    


    while (!win && plays < 9)
    {


        if (player)
            lastPosition = bestMove(positions);
        else
            lastPosition = askPosition(positions, player);

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

void twoPlayers(char positions[])
{
    bool win = false, player = false;
    int plays = 0;

    while (!win && plays < 9)
    {
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
        onePlayer(positions);
    else if (res == "2")
        twoPlayers(positions);
    else if (res == "exit")
        cout << "Thanks for playing!" << endl;
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
