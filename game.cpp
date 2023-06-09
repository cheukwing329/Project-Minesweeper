#include "game.h"

Game::Game(int nDifficulty)
{
	// Initial Game
	if (nDifficulty == Beginner)
	{
		m_nSize = 9;
		m_nMineNum = 10;
	}
	else if (nDifficulty == Intermediate)
	{
		m_nSize = 16;
		m_nMineNum = 40;
	}
	else if (nDifficulty == Advanced)
	{
		m_nSize = 24;
		m_nMineNum = 99;
	}

	// 1.Beginner       –  9 * 9  Board and 10 Mines
	// 2.Intermediate   – 16 * 16 Board and 40 Mines
	// 3.Advanced       – 24 * 24 Board and 99 Mines

	m_nDifficulty = nDifficulty;
	m_nTarget = m_nSize * m_nSize - m_nMineNum;
	BoardInit();
	m_nState = RUNNING;
}

void Game::run()
{
	while (m_nState == RUNNING)
	{
		DrawBoard();
		bool bValid = false;
		int xInput = 0, yInput = 0;
		char cAction = '0';
		while (!bValid)
		{
			cout << "Enter Input(Action(o/f), x, y): ";
			if (cin >> cAction >> xInput >> yInput && InputVaild(cAction, yInput, xInput))
			{
				bValid = true;
			}
			else
			{
				cin.clear();
				cout << "Error input" << endl;
				cin.ignore();
			}
		}
		//Move and 
		if (cAction == 'o')
		{
			OpenMap(yInput, xInput);
		}
		else if (cAction == 'f')
		{
			AddFlag(yInput, xInput);
		}
	}
	DrawBoard();
	if (m_nState == WIN)
	{
		cout << "You WIN!" << endl;
	}
	else if (m_nState == LOSE)
	{
		cout << "You LOSE!" << endl;
	}
}

void Game::BoardInit()
{
	// Initial Board
	for (int i = 0; i < m_nSize; i++)
	{
		mvv_cGame.push_back(vector<char>(m_nSize, NotOpen));
		mvv_nMap.push_back(vector<int>(m_nSize, 0));
	}

	// Initial Mine
	srand((unsigned)time(NULL));
	for (int i = 0; i < m_nMineNum;)
	{
		int y = rand() % m_nSize;
		int x = rand() % m_nSize;

		if (mvv_nMap[y][x] != 999)
		{
			mvv_nMap[y][x] = 999;
			NumInit(y, x);
			i++;
		}
	}
}

void Game::NumInit(int y, int x)
{
	// Add number to adj 8 posn

	// 1 | 2 | 3
	// 4 | m | 5
	// 6 | 7 | 8
	int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	for (int i = 0; i < 9; i++)
	{
		int curx = x + dx[i];
		int cury = y + dy[i];

		if (cury >= 0 && cury < m_nSize && curx >= 0 && curx < m_nSize && mvv_nMap[cury][curx] != 999)
		{
			mvv_nMap[cury][curx] += 1;
		}
	}
}

void Game::DrawBoard()
{
	string separateline = "";

	if (m_nDifficulty == Beginner)
	{
		separateline = "-----------------------------------------";
	}
	else if (m_nDifficulty == Intermediate)
	{
		separateline = "---------------------------------------------------------------------";
	}
	else if (m_nDifficulty == Advanced)
	{
		separateline = "-----------------------------------------------------------------------------------------------------";
	}

	// First line
	cout << endl;
	cout << "   ";
	for (int i = 0; i < m_nSize; i++)
	{
		cout << " |" << setw(2) << setfill(' ') << i;
	}
	cout << " |" << endl;
	cout << separateline << endl;

	//
	for (int i = 0; i < m_nSize; i++)
	{
		cout << setw(2) << setfill(' ') << i << "  |";
		
		for (int j = 0; j < m_nSize; j++)
		{
			/* For Display mine and nuber;
			if (mvv_nMap[i][j] != 999)
			{
				cout << mvv_nMap[i][j];
			}
			else
			{
				cout << 'm';
			}
			*/
			cout << setw(2) << setfill(' ') << mvv_cGame[i][j];
			cout << " |";
		}
		cout << endl;
		cout << separateline << endl;
	}
	cout << endl;
}

bool Game::InputVaild(char Action, int y, int x)
{
	if (y >= 0 && y < m_nSize && x >= 0 && x < m_nSize)
	{
		if (Action == 'o' && mvv_cGame[y][x] == NotOpen)
		{
			return true;
		}
		
		if (Action == 'f' && (mvv_cGame[y][x] == NotOpen || mvv_cGame[y][x] == Flagged))
		{
			return true;
		}
	}

	return false;
}

void Game::OpenMap(int y, int x)
{
	mvv_cGame[y][x] = Map2Game(y, x);
	OpenEmptyMap(y, x);
	if (mvv_cGame[y][x] == '*')
	{
		m_nState = LOSE;
	}
	else
	{
		m_nOpened++;
		if (m_nOpened == m_nTarget)
		{
			m_nState = WIN;
		}
	}
}

void Game::OpenEmptyMap(int y, int x)
{
	// Detect the adj 4 posn if empty()
	// 0 | 1 | 0
	// 2 | m | 3
	// 0 | 4 | 0
	int dy[] = { -1, 0, 0, 1 };
	int dx[] = {  0, -1, 1, 0};

	for (int i = 0; i < 5; i++)
	{
		int curx = x + dx[i];
		int cury = y + dy[i];

		if (cury >= 0 && cury < m_nSize && curx >= 0 && curx < m_nSize)
		{
			if (mvv_cGame[cury][curx] != NotOpen)
			{
				continue;
			}
			else if (mvv_nMap[cury][curx] == 0)
			{
				mvv_cGame[cury][curx] = Map2Game(y, x);
				m_nOpened++;
				OpenEmptyMap(cury, curx);
			}
		}
	}
}

void Game::AddFlag(int y, int x)
{
	if (mvv_cGame[y][x] == NotOpen)
	{
		mvv_cGame[y][x] = Flagged;
	}
	else if (mvv_cGame[y][x] == Flagged)
	{
		mvv_cGame[y][x] = NotOpen;
	}
}

char Game::Map2Game(int y, int x)
{
	if (mvv_nMap[y][x] == 999)
	{
		return '*';
	}
	
	return mvv_nMap[y][x] + '0';
}
