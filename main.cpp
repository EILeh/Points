/* Points
 *
 * Description
 *
 * Program aska the user to give a file's name and tries to open it. If file
 * can't be opened, program prints an error and ends to a return value
 * EXIT_FAILURE. If file can be opened, program reads every line from the file
 * and counts every players' overall points. Program prints the players' and
 * their points in aplhabetical order and without dublicates. Ends to a return
 * value EXIT_SUCCESS.
 *
 * Writer of the program
 *
 * Name: EILeh
 *
 */


#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string file_name = "";

    cout << "Input file: ";
    getline(cin, file_name);

    map<string, int> points;

    string row;

    ifstream file_object(file_name);


    // If file can't opened, prints an error.
    if ( !file_object )
    {
        cout << "Error! The file " << file_name << " cannot be opened.";

        file_object.close();

        return EXIT_FAILURE;
    }

    else
    {
        cout << "Final scores:" << endl;

        while ( getline(file_object, row) )
        {
            // Finds from every fileline a separator ":" and stores its'
            // location to a variable.
            string::size_type position = row.find(":");

            // If position is not the end of the string (string::npos = "no po-
            // sition" constant which represents the end of the string and means
            // that the particular string hasn't been found).
            if ( position != string::npos )
            {
                // The map key is found between the variable's row's index 0 and
                // the variable position.
                string key = row.substr(0, position);

                // Current player is at the position key.
                string current_player = key;

                // Initializes the vector splitted_vector.
                vector<string> splitted_vector = {};

                // Initializes the string.
                string substring = "";

                // Initializes the separator char that is searched.
                char separator = ':';

                // Goes through the file's lines char by char and checks the po-
                // sition where the variable separator is located in the variab-
                // le row.
                for ( char c : row )
                {
                    // If separator is found and substring is not empty, adds
                    // the substring to a vector splitted_vector and then clears
                    // the substring.
                    if ( c == separator && !(substring.empty()))
                    {
                        splitted_vector.push_back(substring);
                        substring.clear();
                    }

                    // If current char is not separator, the currents char is
                    // added to the substring.
                    else
                    {
                        substring += c;
                    }

                }

                // The map value is found between the variable's row's position
                // and index 1.
                int value = stoi(row.substr(position + 1));

                // If current player is found from the map points, new points
                // are added to player's previous points.
                if ( points.find(current_player) != points.end() )
                {
                    points.at(current_player) += value;
                }

                // If current player is not found from the map points, a new
                // key-value -pair is added to the map.
                else
                {
                    points.insert( {key, value } );
                }
            }
        }
    }

    // Prints the information from the map.
    for ( auto &i : points )
    {
        cout << i.first << ": " << i.second << endl;
    }

    // Closes the file.
    file_object.close();

    return EXIT_SUCCESS;
}
