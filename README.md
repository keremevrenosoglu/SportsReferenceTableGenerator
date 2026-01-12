# SportsReferenceTableGenerator
## Overview
The idea is to take a JSON file structured like that included in the sample file, and create a matrix that can be used to output a table following the format of those found on Sports Reference websites. Specifically, this table will present teams' records against each other with each row displaying how many wins a team has against each of the teams labeled by the columns.


## Implementation
In order to accomplish this goal, a common library that is used by large companies for parsing JSON in C++ was used to first retrieve the necessary data. This was then transferred over to a map providing more simple access where a team's list of opponents could be accessed with the team's name, and the win count against each team could be reached by further specifying the opponent's name. Finally, this map is iterated over in order to actually display the results of the table. More specific details are included in the comments of the cpp file.


## How to Use
The only outside package appearing here is the one used for parsing the JSON from [nlohmann/json](https://github.com/nlohmann/json), as such, just need to make sure this is accessible and addressed at compile time.  

One way to install is using the method below:  
`brew install nlohmann-json`

The code could then be compiled with:  
`c++ tableGenerator.cpp -I$(brew --prefix nlohmann-json)/include -std=c++11 -o tableGenerator`

When you run it, such as with:  
`./tableGenerator`

It will ask for the name of a file. So long as you provide a valid name or path to a JSON file structured as the sample, or use the sample itself, the program should behave as intended.
