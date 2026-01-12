#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

/*
 We use this function to initially create the matrix where
 each row and column coincides with a certain team and the
 value found at each entry is the number of wins the row 
 team has against the column team. This matrix will be
 returned as a map of maps reflecting that structure.
 The name of a JSON file is taken as an argument in 
 order to read the data that will fill the matrix.
 */
map<string, map<string, int>> createMatrix(string fileName) {
    // First parse the JSON in order to get an object
    // containing the data
    ifstream file(fileName);
    json data = json::parse(file);
    file.close();
    map<string, map<string, int>> matrix;
    
    /*
     The final output of the program could've been
     achieved without this next step but we iterate
     over the object in order to transfer the data to
     the return map, demonstrating our knowledge of
     data structures and giving the caller of the
     function a more straightforward to work with
     container from the standard library if desired.
     The outer loop here goes through each greater 
     entry for each team. Technically only needed to
     go through half of these and could've entered 
     losses against an opponent as that opponent's wins
     but leaving this as is for now for time reasons. 
    */
    for (const auto& teamEntry : data.items()) {
        /*
        A team can't have a record against itself
        so this value is set to -1. There will still
        be an entry in the table though where the row
        matches the column hence why this case was 
        handled.
        */
        matrix[teamEntry.key()][teamEntry.key()] = -1;

        // Here we loop through the records against each
        // opponent, only collecting the number of wins
        // which will be needed for the table
        for (const auto& opponent : teamEntry.value().items()) {
            matrix[teamEntry.key()][opponent.key()] = opponent.value()["W"];
        }
    }

    return matrix;
}


// This function will simply then take the matrix
// represented by the map and output the table to the
// format used by Sports Reference sites
void displayTable(map<string, map<string, int>> matrix) {
    // Denotes that each row and column references a
    // team name
    cout << "\n" << setw(4) << left << "Tm" << "  ";
    
    // Print the team names for each column
    for (const auto& teamCol : matrix) {
        cout << setw(4) << teamCol.first << " ";
    }

    // Go through the records against each opponent,
    // displaying the opponent's name at the start 
    // of the row, followed by the win count for each
    // entry
    for (const auto& teamRow : matrix) {
        cout << "\n" << setw(4) << left << teamRow.first << " ";

        for (const auto& opponent : teamRow.second) {
            // The spot for a team's wins against itself
            // is simply marked with "--"
            if (opponent.first == teamRow.first) {
                cout << setw(4) << right << "--" << " ";
            }
            else {
                cout << setw(4) << right << matrix[teamRow.first][opponent.first] << " ";
            }
        }
    }

    // Same process from the beginning is used to 
    // label the columns at the bottom
    cout << "\n" << setw(4) << left << "Tm" << "  ";
    for (const auto& teamCol : matrix) {
        cout << setw(4) << teamCol.first << " ";
    }
}

// main asks for the name/path of a valid JSON
// file with the correct structure, using the
// functions defined above to then create and
// output the table
int main()
{
    string fileName;
    cout << "Enter name of JSON file: ";
    cin >> fileName ;
    displayTable(createMatrix(fileName));
}