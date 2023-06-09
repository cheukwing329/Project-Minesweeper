// minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "game.h"

using namespace std;
int main()
{
    bool bValid = false;
    int nDifficulty;

    while (!bValid)
    {
        int nInput = 0;
        cout << "Choose difficulty (1.Beginner; 2.Intermediate; 3.Advanced): ";
        if (cin >> nInput && nInput <= 3 && nInput >=1)
        {
            bValid = true;
            nDifficulty = nInput;
        }
        else
        {
            cin.clear();
            cout << "Error input" << endl;
            cin.ignore();
        }
    }

    Game game(nDifficulty);
    game.run();
    return 0;
}


// Flow:
// 1. Choose difficulty
// 2. Generate mine
// 3. Generate number
// 4. Game start

// Game Start
// 1. Draw board
// 2. Input
// 3. Verify Input (If not valid, re)
// 4. Open cell
// 5. If mine = end; else = detect win; else continue
