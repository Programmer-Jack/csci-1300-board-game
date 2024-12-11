#include "Board.h"
#include "Player.h"
#include "Utilities.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

void displayTitle()
{
    //const string TITLE_SRC_PATH = "data/TITLE.txt";
    const string TITLE_SHADOW_SRC_PATH = "data/TITLE_SHADOW.txt";

    ifstream title_src(TITLE_SHADOW_SRC_PATH);
    string current_line = "";

    if (!title_src.fail())
    {
        while (getline(title_src, current_line))
        {
            cout << current_line << endl;
        }
    }
    else
    {
        cout << "!!! Dude theres an error with the title file. !!!\n";
    }

    title_src.close();
}

vector<Player> tryGetCharacterListFromFile()
{
    vector<Player> player_character_list; // Create empty list to be added to

    ifstream input_file("data/characters.txt");

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
            Utilities::split(current_line, '|', current_line_stats, STAT_COUNT);

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
    else
    {
        cout << "!!! Dude theres an error with the characters file. !!!\n";
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

Player choosePlayerPath(Player target_player, string player_name)
{
    int pathIndex = Utilities::getIntValueInRange(1, 2, player_name + ", select a path:\n"
                                                        "1: Cub Training\n"
                                                        "2: Straight to the Pride Lands\n");

    switch (pathIndex)
    {
    case 1:
        target_player.trainCub(500, 500, 1000);
        break;
    case 2:
        target_player.toPrideLands();
        break;
    default:
        cout << "??? OW DID WE GET HERE?\nA path index outside of range made it through the system somehow. ???\n\n";
        break;
    }

    return target_player;
}

bool gameCycle(Board board);

int main()
{
    // Self-explanatory
    displayTitle();

    // Display player character options
    vector<Player> player_character_list = tryGetCharacterListFromFile();
    displayPlayerSet(player_character_list);

    // Prompt each player to choose a character
    Player player_1 = getPlayerFromOptions(player_character_list, "\nPLAYER 1, enter the name of your lion: ");
    player_1.printStats();
    Player player_2 = getPlayerFromOptions(player_character_list, "\nPLAYER 2, enter the name of your lion: ");
    player_2.printStats();

    // Prompt each player to choose a path type
    player_1 = choosePlayerPath(player_1, player_1.getName());
    player_2 = choosePlayerPath(player_2, player_2.getName());

    // Create a new board and begin the game
    Board board(2);
    bool win = gameCycle(board);

    if (win) cout << "\nSomebody won idk\n\n";

    return 0;
}

bool gameCycle(Board board)
{
    int turn_index;
    int player_turn_index = 0;

    while (true)
    {
        // Display round and player info
        cout << "\nROUND " << turn_index << endl
             << "PLAYER " << player_turn_index + 1 << "'s TURN\n\n";

        // Display the board
        board.displayBoard();

        // Prompt player for a command input
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

                cout << "SPINNER RESULT: Move " << rand_move_spaces << " spaces!\n\n";

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