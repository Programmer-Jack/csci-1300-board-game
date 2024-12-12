#include "Board.h"
#include "Player.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

void displayTitle()
{
    //const string TITLE_SRC_PATH = "data/TITLE.txt";
    const string TITLE_SHADOW_SRC_PATH = "data/TITLE_A.txt";

    ifstream title_src(TITLE_SHADOW_SRC_PATH);
    string current_line = "";

    if (!title_src.fail())
    {
        while (getline(title_src, current_line))
        {
            cout << current_line << endl;
        }
        cout << endl;
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
    cout << endl;
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
        Utilities::throwNonexistentLionErrorMsg();
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
        cout << "??? HOW DID WE GET HERE?\nA path index outside of range made it through the system somehow. ???\n\n";
        break;
    }

    return target_player;
}

// Function that executes bulk of the work; declaration here, definition at bottom for organization
bool cycleGameUntilEnd(Board board, Player player_1, Player player_2); 

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
    bool win = cycleGameUntilEnd(board, player_1, player_2);

    if (win) cout << "\nSomebody won idk\n\n";

    return 0;
}

bool cycleGameUntilEnd(Board board, Player player_1, Player player_2)
{
    Player players[2] =
    {
        player_1,
        player_2
    };

    int round = 1;
    int current_player_index;

    while (true)
    {
        // Set current player, alternate every round
        current_player_index = round % 2; 
        Player current_player = players[current_player_index];

        // Display round and player info
        cout << "********************************************"
             << "\nROUND " << round << endl
             << players[current_player_index].getName() << "'s turn (PLAYER " << current_player_index + 1 << ")\n\n";

        // Display the board
        board.displayBoard();

        bool end_turn = false;
        while (!end_turn)
        {
            // Prompt player for a command input
            int input = Utilities::getIntValueInRange(1, 6, "Select a command.\n"
                                                            "1. ROLL THE DIE: Move forward a 1~6 tiles (\"die\" is the singular of \"dice\" so don't correct me)\n"
                                                            "2. WHO AM I? View character information.\n"
                                                            "3. WHERE AM I? Check current position if it isn't obvious from the board.\n"
                                                            "4. VIEW ADVISOR DATA.\n"
                                                            "5. Exit Game\n");

            switch (input)
            {
            case 1: // ROLL THE DIE
            {
                cout << "ROLLING THE DIE...\n\n";

                int rand_move_spaces = rand() % 6 + 1;

                cout << "\033[48;2;63;63;63m" << "THE DIE HATH DETERMINED YOUR FATE: You will move " << rand_move_spaces << " spaces.\033[0m\n\n";

                for (int i = 0; i < rand_move_spaces; i++)
                {
                    bool win = board.movePlayer(current_player_index);
                    if (win)
                    {
                        return true;
                    }
                    end_turn = true; // Ends turn.
                }
                break;
            }
            case 2: // WHO AM I?
            {
                // Doing these things step-by-step aids readability and understandability.
                // I've found that sometimes the hardest part of writing code is just understanding
                // what I've already written and maintaining the logic in my own brain...
                current_player.printStats();
                cout << endl;
                break;
            }
            case 3: // WHERE AM I?
            {
                cout << "You are at tile " << board.getPlayerPosition(current_player_index) << ".\n\n";
                break;
            }
            case 4: // ADVISOR DATA
            {

                break;
            }
            case 5: // Exit Game
            {
                cout << "\nYou have exited the game.\n";
                return false;
            }
            default:
            {
                cout << "HOW DID WE GET HERE? A value out of range somehow made it through and you need to go fix it, Jack!\n";
                break;
            }
            }
        }

        // Last step: increment round counter
        round++;
    }

    return false;
}