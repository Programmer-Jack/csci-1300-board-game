#ifndef SPLIT_H
#define SPLIT_H

#include "Player.h"
#include <vector>
using namespace std;

class Split
{
public:
    vector<Player> splitPlayers(string input, char delimiter, vector<string> playerList)
    {
        // define a temporary string and helper variables
        string temp = "";

        // check for empty input
        if (input == "")
        {
            return vector<Player>();
        }

        else
        {
            for (unsigned int i = 0; i < input.length(); i++)
            {
                // Check for delimiter
                if (input[i] != delimiter)
                {
                    // If the current character is not a delimeter, add it to the temporary string
                    temp = temp + input[i];
                }
                // if the current character is a delimeter
                else
                {
                    // add temporary string to the vector
                    playerList.push_back(temp);
                    // set temp to an empty string
                    temp = "";
                }
            }
            
            playerList.push_back(temp);
        }

        return vector<Player>();
    }
};

#endif