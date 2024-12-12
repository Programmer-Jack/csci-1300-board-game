#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
using namespace std;

namespace Utilities
{
    // Hey look, I made a new Doxygen comment. Learn new skills every day I guess

    /// @brief A function that sorts elements of a single string (i.e., a line from a file)
    /// separated by a delimiter into a string array. Lightly modified from original.
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

    void throwErrorMessage(const string prompts[], unsigned int prompt_count)
    {
        unsigned int randIndex = rand() % prompt_count;
        string prompt = prompts[randIndex];
        cout << endl << "\033[48;2;255;000;000m" << prompt << "\033[0m" << endl;
    }

    void throwNonexistentLionErrorMsg()
    {
        const string MESSAGES[] = 
        {
            "Who?",
            "Who's that?",
            "ERROR: NONEXISTENT_LION_EXCEPTION",
            "Haven't heard the name, sorry.",
            "Can't say I know who that is.",
            "Read from the list and try again."
        };
        unsigned int msg_count = 6;
        throwErrorMessage(MESSAGES, msg_count);
    }

    /// @brief Everybody makes mistakes! Tell the player to give it another go.
    void throwInvalidErrorMsg()
    {
        const string MESSAGES[] =
        {
            "Invalid input. Try again.",
            "Oh nooo, you're stupid! Invalid input.",
            "Play the game right and we can both get this over with.",
            "Did you ever learn how to use a keyboard?"
        };
        unsigned int msg_count = 4;
        throwErrorMessage(MESSAGES, msg_count);
    }

    void throwOutOfRangeErrorMsg()
    {
        const string MESSAGES[] =
        {
            "Not in range. Try again.",
            "Read your options again and give it another shot.",
            "Come on now quit playing around and input a legitimate option",
            "Why did you type that? That's not a choice I gave you."
        };
        unsigned int msg_count = 4;
        throwErrorMessage(MESSAGES, msg_count);
    }

    int getIntValueInRange(int min, int max, string prompt)
    {
        while (true)
        {
            cout << endl << prompt << endl;
            string input;
            cin >> input;
            cout << endl;

            if (!validateInt(input))
            {
                throwInvalidErrorMsg();
            }
            else
            {
                int selected_index = stoi(input);

                if (selected_index < min || selected_index > max)
                {
                    throwOutOfRangeErrorMsg();
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