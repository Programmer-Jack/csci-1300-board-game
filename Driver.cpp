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
            int new_age = stoi(current_line_stats[1]);
            int new_strength = stoi(current_line_stats[2]);
            int new_stamina = stoi(current_line_stats[3]);
            int new_wisdom = stoi(current_line_stats[4]);
            int new_pride_points = stoi(current_line_stats[5]);
            Player new_player = Player(new_name, new_age, new_strength, new_stamina, new_wisdom, new_pride_points);

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

Player getPlayerFromOptions(vector<Player> options, string prompt)
{
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

bool gameCycle(Board board);

Player choosePlayerPath(Player target_player, string prompt);

int main()
{
    vector<Player> player_character_list = tryGetCharacterListFromFile();
    displayPlayerSet(player_character_list);

    Player player_1 = getPlayerFromOptions(player_character_list, "\nPLAYER 1, enter the name of your lion: ");
    player_1.printStats();
    Player player_2 = getPlayerFromOptions(player_character_list, "\nPLAYER 2, enter the name of your lion: ");
    player_2.printStats();

    player_1 = choosePlayerPath(player_1, "Player 1, select a path:\n"
                                          "0: Cub Training\n"
                                          "1: Straight to the Pride Lands\n");
    player_2 = choosePlayerPath(player_2, "Player 2, select a path:\n"
                                          "0: Cub Training\n"
                                          "1: Straight to the Pride Lands\n");

    Board board(2);
    gameCycle(board);

    return 0;
}

bool gameCycle(Board board)
{
    int turn_index = 1;
    int player_turn_index = 0;

    while (true)
    {
        cout << "ROUND " << turn_index << endl
             << "PLAYER " << player_turn_index + 1 << "'s TURN\n";

        board.displayBoard();

        cout << "\nSelect a command:\n"
                "0: move forward\n"
                "1: exit game\n";
        string input;
        cin >> input;

        switch (stoi(input))
        {
            case 0:
            {
                turn_index++;
                cout << "\nSPINNING FOR RANDOM FORWARD MOVEMENT...\n\n";

                int rand_move_spaces = rand() % 6 + 1;

                cout << "SPINNER RESULT: Move " << rand_move_spaces << " spaces!" << endl;

                for (int i = 0; i < rand_move_spaces; i++)
                {
                    bool win = board.movePlayer(player_turn_index);
                    if (win)
                        return true;
                }
                break;
            }
            case 1:
            {
                cout << "\nEXIT GAME";
                return false;
            }
            default:
            {
                cout << "INVALID COMMAND\n";
                break;
            }
        }
    
        player_turn_index = turn_index % 2;
    }

    return false;
}

Player choosePlayerPath(Player target_player, string prompt)
{
    cout << prompt;
    string input;
    cin >> input;

    switch (stoi(input))
    {
        case 0:
            target_player.trainCub(500, 500, 1000);
        case 1:
            target_player.toPrideLands();
    }

    return target_player;
}