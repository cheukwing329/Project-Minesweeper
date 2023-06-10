# Project-Minesweeper
This is a personal project that build a console game application, minesweeper

IF you want to try, feel free to download minesweeper.exe

# User Flow
Before game start, player need to input 1 or 2 or 3 to choose the difficulty.

1. Beginner       –  9 * 9  Board and 10 Mines

2. Intermediate   – 16 * 16 Board and 40 Mines

3. Advanced       – 24 * 24 Board and 99 Mines

After valid input, game start:

Each step, player is needed to input 3 elements, Action, x and y.

Action are o for open and f for flag; x and y are limited to the board size shown before.

e.g. [ o 1 5 ], [ f 5 8 ]

WIN condition:  Open all non mine cell

LOSE condition: Open any mine cell


# Application Flow
Before game start, the game will ask for the input of difficulty(1, 2, 3).

After detected a vaild input, game will be initialized by calling: 
>		Game game(nDifficulty);

This function helps to define the board size, number of mine, number of target, game state, and call the BoardInit();

Regarding BoardInit(), this function is to initialize the board vector and genrate the mine randomly by
>		srand((unsigned)time(NULL));
>		
>		int y = rand() % m_nSize;
>		
>		int x = rand() % m_nSize;

When each mine are generated, their adjacent 8 cell will add 1.

After all mine are ready, game start by calling
>		game.run();

I have used a varible m_nState to record the game state ( RUNNING, WIN, LOSE, STOPPED ).

While game state is RUNNING, the gaem will first call the function
>		DrawBoard();

to show the board in cmd window. 

Then, it will ask for input (Action, x, y)

There are 2 acceptable input for action, o and f for open and flag respectively.
As well as x and y will be limimted by the board size.

Apart from those limit, there are also a function
>		InputVaild(Action, y, x)

This function helps to detect the chosen cell is not opened.

After valid input, the program will call the corresponding function regarding action.

For flag:
>		AddFlag(yInput, xInput);

This function will simply flag or unflag the chosen cell.

For open:
>		OpenMap(yInput, xInput);

This function will not only open the chosen cell, but also open the adjacent 4 cell if they are empty (i.e. number = 0).

The win/lose condition will also be detected after the seleted cell opened.

As I do not added any time limit to game, the game will just simple detect the opened cell and its number.

For WIN condition, if number of opened cell equal to targer, game end with YOU WIN!;

For LOSE condition, if any mine cell is opened, game end with YOU LOSE!;
