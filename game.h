#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <stdlib.h> 
#include <iomanip>

using namespace std;

enum Difficulty { Beginner = 1, Intermediate, Advanced};

enum State { RUNNING, WIN, LOSE, STOPPED };

#define NotOpen '-'
#define Flagged 'f'

class Game
{
private:
	int m_nSize = 0;
	int m_nMineNum = 0;
	int m_nDifficulty = 0;
	int m_nState = STOPPED;

	vector<vector<char>> mvv_cGame;				// For game display
	vector<vector<int>> mvv_nMap;				// For mine and number

	int m_nOpened = 0;
	int m_nTarget = 0;

public:
	Game(int nDifficulty);			
	void run();										// Game Main function
	void BoardInit();
	void NumInit(int y, int x);
	void DrawBoard();				
	bool InputVaild(char Action, int y, int x);		// Check Move
	void OpenMap(int y, int x);						// Open the input location
	void OpenEmptyMap(int y, int x);				// Open the empty next to input;
	void AddFlag(int y, int x);						// Add or remove flag
	char Map2Game(int y,int x);						// mvv_cGame = Map2Game(y, x) to convert int to char
};


#endif // !GAME_H

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
