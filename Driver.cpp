#include "Board.h"
#include "Player.h"
#include "Split.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

vector<Player> tryGetCharacterListFromFile()
{
    vector<Player> player_character_list; // Create empty list to be added to

    ifstream input_file("characters.txt");

    if (!input_file.fail())
    {
        string current_line;
        int line_count = 0;

        const int STAT_COUNT = 6;
        string current_line_stats[STAT_COUNT];

        while (getline(input_file, current_line))
        {
             // Skip first line of file
            if (line_count == 0)
            {
                line_count++;
                continue;
            }

            // Split each line's contents into statistic entries in the statistic array
            Split::split(current_line, '|', current_line_stats, STAT_COUNT);

            // Construct new Player
            string new_name = current_line_stats[0];
            int new_strength = stoi(current_line_stats[2]);
            int new_stamina = stoi(current_line_stats[3]);
            int new_wisdom = stoi(current_line_stats[4]);
            Player new_player = Player(new_name, new_strength, new_stamina, new_wisdom);

            // Add player character to list
            player_character_list.push_back(new_player);

            line_count++;
        }
    }

    input_file.close();

    return player_character_list;
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

Player getPlayerFromOptions(vector<Player> options, string prompt)
{
    int used_index = -1;
    while (true)
    {
        string input_name;
        cout << prompt;
        cin >> input_name;

        for (unsigned int i = 0; i < options.size(); i++)
        {
            if (input_name == options.at(i).getName())
            {
                return options.at(i);
            }
        }
        cout << "\nThat lion does not exist.\n";
    }
}

int main()
{
    vector<Player> player_character_list = tryGetCharacterListFromFile();
    displayPlayerSet(player_character_list);

    Player player_1 = getPlayerFromOptions(player_character_list, "\nPLAYER 1, please enter the name of your lion: ");
    Player player_2 = getPlayerFromOptions(player_character_list, "\nPLAYER 2, please enter the name of your lion: ");

    // Board board(2);
    // gameCycle(board);

    return 0;
}