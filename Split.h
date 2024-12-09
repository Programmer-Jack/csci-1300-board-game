#ifndef SPLIT_H
#define SPLIT_H

#include "Player.h"
#include <vector>
using namespace std;

namespace Split
{
    int split(string input_line, char delimiter, string line_as_string_array[], int arr_size)
    {
        // define a temporary string and helper variables
        string temp = "";
        int size = 0;

        // check for empty input
        if (input_line == "")
        {
            return size;
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
                        return size;
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
                return -1;
            }
            // add temporary string to the array
            else
            {
                line_as_string_array[size - 1] = temp;
            }
        }
        return size;
    }
};

#endif