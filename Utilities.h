#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
using namespace std;

namespace Utilities
{
    // Hey look, I made a new Doxygen comment. Learn new skills every day I guess

    /// @brief A function that sorts elements of a single string (i.e., a line from a file)
    /// separated by a delimiter into a string array.
    /// @param input_line 
    /// @param delimiter 
    /// @param line_as_string_array 
    /// @param arr_size 
    void split(string input_line, char delimiter, string line_as_string_array[], int arr_size)
    {
        // define a temporary string and helper variables
        string temp = "";
        int size = 0;

        // check for empty input
        if (input_line == "")
        {
            return;
        }
        else
        {
            for (unsigned int i = 0; i < input_line.length(); i++)
            {
                // Check for delimiter
                if (input_line[i] != delimiter)
                {
                    // If the current character is not a delimeter, add it to the temporary string
                    temp = temp + input_line[i];
                }
                // if the current chracter is a delimeter
                else
                {
                    size++;
                    // check if size > arrSize
                    if (size > arr_size)
                    {
                        size = -1;
                        return;
                    }
                    // add temporary string to the array
                    // set temp to an empty string
                    // check if last string is the longest
                    else
                    {
                        line_as_string_array[size - 1] = temp;
                        temp = "";
                    }
                }
            }
            // Account for final string
            size++;
            // check if size > arrSize
            if (size > arr_size)
            {
                return;
            }
            // add temporary string to the array
            else
            {
                line_as_string_array[size - 1] = temp;
            }
        }
        return;
    }

    /// @param input string to be tested
    /// @return true if @p input contains only 0 through 9.
    bool validateInt(string stringToTest)
    {
        int length = stringToTest.length();

        for (int c = 0; c < length; c++)
        {
            if (length == 0)
            {
                return false;
            }

            // IF INPUT IS NOT 0~9
            if (stringToTest[c] < 48 ||
                stringToTest[c] > 57)
            {
                return false;
            }
        }
        return true;
    }

    /// @brief Everybody makes mistakes! Tell the player to give it another go.
    void throwInvalidErrorMsg()
    {
        string messages[] =
        {
            "Invalid input. Try again.",
            "Oh nooo, you're stupid! Invalid input.",
            "Dude come on. Just play the game right. Not that hard.",
            "Did you ever learn how to use a keyboard?"
        };

        // HAD ISSUES WHERE static_cast<int>(sizeof(messages)) MESSED UP THE OUTPUT. FOR NOW USE INT LITERAL
        unsigned int randIndex = rand() % 4;

        cout << endl << messages[randIndex] << endl << endl;
    }

    void throwOutOfRangeErrorMsg()
    {
        string messages[] =
        {
            "Not in range. Try again.",
            "Read your options again and give it another shot.",
            "Come ON now we don't have TIME for this",
            "THAT ISN'T AN OPTION WHY DID YOU TYPE THAT",
            "You've failed me"
        };

        // HAD ISSUES WHERE static_cast<int>(sizeof(messages)) MESSED UP THE OUTPUT. FOR NOW USE INT LITERAL
        unsigned int randIndex = rand() % 5;

        cout << endl << messages[randIndex] << endl << endl;
    }

    int getIntValueInRange(int min, int max, string prompt)
    {
        while (true)
        {
            cout << endl << prompt << endl;
            string input;
            cin >> input;

            if (!validateInt(input))
            {
                throwInvalidErrorMsg();
            }
            else
            {
                int selected_index = stoi(input);

                if (selected_index < min || selected_index > max)
                {
                    Utilities::throwOutOfRangeErrorMsg();
                }
                else
                {
                    return selected_index;
                }
            }
        }
    }
};

#endif