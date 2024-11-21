#include "Board.h"

using namespace std;

int main()
{
    Board board(2);

    // Basic logic cycle.
    while (true)
    {
        // Update display.
        board.displayBoard();
        // Prompt user.
        cout << "Please enter a command... ";

        // Take input.
        string input;
        cin >> input;
        cout << endl;

        // Do stuff based on that input.
        // Yeah yeah I know, a bunch of if statements ain't pretty,
        // but C++ doesn't allow string switches so here we are
        if (input == "help")
        {
            cout << "COMMANDS\n"
                 << "1: advance player 1 forward\n"
                 << "2: advance player 2 forward\n"
                 << "exit: exit\n\n";
        }
        else if (input == "1")
        {
            board.movePlayer(0);
        }
        else if (input == "2")
        {
            board.movePlayer(1);
        }
        else if (input == "exit")
        {
            break;
        }
        else
        {
            cout << "Invalid command. (Try \"help\"...)\n\n";
        }
    }

    return 0;
}