#include "Board.h"
#include "Player.h"
#include "Split.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

bool tryGetCharactersFromFile(vector<string> outputList)
{
    ifstream input_file("characters.txt");
    string current_line;

    if (!input_file.fail())
    {
        //Split Splitter;

        while (getline(input_file, current_line))
        {
            //Splitter.splitPlayers(current_line, '|', outputList);
        }
    }

    input_file.close();

    return true;
}

void displayPlayerSet(vector<Player> characters)
{
    for (unsigned int i = 0; i < characters.size(); i++)
    {
        characters.at(i).printStats();
    }
}

bool gameCycle(Board board)
{
    int turn_index = 0;
    int player_turn_index = 0;
    //bool win = false;

    while (true)
    {
        cout << "\n\n*****START GAME CYCLE******\n\n";

        cout << "\n\nDISPLAY BOARD\n\n";
        board.displayBoard();

        cout << "\n\nGET INPUT\n\n";
        string input;
        cin >> input;
        
        if (input == "move")
        {
            bool win = board.movePlayer(player_turn_index);

            if (win) return win;

            turn_index++;
        }
        else if (input == "exit")
        {
            return false;
        }
        else
        {
            cout << "INVALID INPUT" << endl;
        }

        player_turn_index = turn_index % 2;

        cout << "Round " << turn_index << "; Player " << player_turn_index << endl;

        cout << "\n\n*****END OF GAME CYCLE*****\n\n";
    }
}

int main()
{
    Board board(2);
    gameCycle(board);

    return 0;
}