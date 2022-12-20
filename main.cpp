#include <iostream>
#include <climits>
#include <string>
#include <map>
#include <cmath>
using namespace std;

void resetBoard(char positions[]) {
    for (int i = 0; i < 9; i++)
        positions[i] = 49 + i;
}

void showGrid(char positions[]) {
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

int askPosition(char positions[], bool player) {
    showGrid(positions);
    string res;

    cout << "Player " << player + 1 << ": Position to play? (1-9)" << endl;
    cin >> res;

    try {
        if (stoi(res) < 1 || stoi(res) > 9)
            throw 505;

        if (positions[stoi(res) - 1] == 'O' || positions[stoi(res) - 1] == 'X') {
            cout << "Invalid response" << endl;
            return askPosition(positions, player);
        }
        else {
            positions[stoi(res) - 1] = (player ? 'X' : 'O');
            return stoi(res) - 1;
        }
    }
    catch (...) {
        cout << "Invalid response" << endl;
        return askPosition(positions, player);
    }
}

bool checkWin(char positions[], int lastPosition, bool player) {
    int combinations[9][4][2] = {
        {{1, 2}, {4, 8}, {3, 6}},
        {{0, 2}, {4, 7}},
        {{0, 1}, {5, 8}, {4, 6}},
        {{4, 5}, {0, 6}},
        {{3, 5}, {1, 7}, {0, 8}, {2, 6}},
        {{2, 8}, {3, 4}},
        {{0, 3}, {7, 8}, {2, 4}},
        {{1, 4}, {6, 8}},
        {{2, 5}, {6, 7}, {0, 4}}
    };

    int posibilities = lastPosition == 4 ? 4 : 3 - lastPosition % 2;

    for (int i = 0; i < posibilities; i++) {
        int total = 0;
        for (int j = 0; j < 2; j++) {
            if (positions[combinations[lastPosition][i][j]] == (player ? 'X' : 'O')) 
                total++;
            if (total == 2)
                return true;
        }
    }
    return false;
}

int checkKey(char positions[]) {
    int key = 0;
    for (int i = 0; i < 9; i++) {
        if (positions[i] == 'X')
            key = key + ((int) pow(3.0, i) * 2);
        else if (positions[i] == 'O')
            key = key + ((int) pow(3.0, i));
    }
    return key;
}

int minimax(char positions[], int depth, bool player, int lastPosition, map<int, int> &results, int plays) {
    int key = checkKey(positions);
    int score;

    if(results.find(key) == results.end()) {
        score = checkWin(positions, lastPosition, !player) ? (!player ? 10 : -10) : 0;
        if(score != 0)
            results[key] = score;
    } else 
        score = results[key];

    // Si Gana el Bot/Humano
    if (score != 0)
        return score;
    // Empate
    if (plays == 9)
        return 0;
    // si player es true, es el jugador 2 por ende el bot
    if (player) {
        int maximum = INT_MIN;
        for (int i = 0; i < 9; i++) {
            if (positions[i] != 'X' && positions[i] != 'O') {
                positions[i] = 'X';
                int mx = minimax(positions, depth + 1, !player, i, results, plays+1);
                maximum = max(maximum, mx);
                positions[i] = i + 49;
                plays--;
            }
        }
        return maximum - depth;
    }
    else {
        int minimum = INT_MAX;
        for (int i = 0; i < 9; i++) {
            if (positions[i] != 'X' && positions[i] != 'O') {
                positions[i] = 'O';
                int mm = minimax(positions, depth + 1, !player, i, results, plays+1);
                minimum = min(minimum, mm);
                positions[i] = i + 49;
                plays--;
            }
        }
        return minimum - depth;
    }
}

int bestMove(char positions[], map<int, int> &results, int plays) {
    int bestVal = INT_MIN;
    int OptiMove;
    for (int i = 0; i < 9; i++) {
        if (positions[i] != 'X' && positions[i] != 'O') {
            positions[i] = 'X';

            int ValMove = minimax(positions, 0, false, i, results, plays);
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

void game (int numberPlayer) {
    bool win = false, player = false;
    int plays = 0, lastPosition;
    string again = "1";

    map<int, int> results; 

    char positions[9];

    for (int i = 0; i < 9; i++)
        positions[i] = i + 49;

    while (again == "1") {
        while (!win && plays < 9) {
            if (player)
                if (!numberPlayer)
                    lastPosition = bestMove(positions, results, plays);
                else 
                    lastPosition = askPosition(positions, player);
            else 
                lastPosition = askPosition(positions, player);

            win = checkWin(positions, lastPosition, player);
            player = !player;
            plays++;
        }

        if (win) {
            showGrid(positions);
            player = !player;

            cout << endl
                << "Player " << player + 1 << " won!" << endl;
        }
        else {
            cout << endl
                << "It was a tie!" << endl;
        }

        cout<<"Do you want to play again? (1/2)"<<endl;
        cin>>again;

        resetBoard(positions);
        player = !player;
        plays = 0; win = false;
    }

    cout << "Thanks for playing!" << endl;
}

int main() {
    cout << "---------------------------------------------" << endl;
    cout << "TIC TAC TOE" << endl;
    cout << "----------------------------------------------" << endl;
    cout << endl;

    string res;
    cout << "How many players? (1/2)" << endl;
    cin >> res;

    if (res == "1" || res == "2")
        game(stoi(res) - 1);
    else 
        cout << "Invalid response" << endl;

    return 0;
}
