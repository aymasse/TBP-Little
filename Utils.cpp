#include "Utils.h"

vector<Coordinates> getCoordinates(string fileName) {
    vector<Coordinates> coordinates = vector<Coordinates>();
    string currentLine;
    ifstream file(fileName);
    string delimiter = " ";

    //Check if file is readable
    if (file.good()) {
        while (getline(file, currentLine)) {
            size_t pos = 0;
            int index = 0;
            float x = 0;
            float y = 0;

            //Getting tower index
            pos = currentLine.find(delimiter);

            if (pos != string::npos) {
                try {
                    index = stoi(currentLine.substr(0, pos));
                } catch (...) {
                    cout << "Error while converting index into an integer."
                         << "Setting to default value : 0."
                         << endl;
                    index = 0;
                }

                currentLine.erase(0, pos + delimiter.length());
            }

            //Getting x coordinate
            pos = currentLine.find(delimiter);

            if (pos != string::npos) {
                try {
                    x = stof(currentLine.substr(0, pos));
                } catch (...) {
                    cout << "Error while converting x into a float."
                         << "Setting to default value : 0."
                         << endl;
                    x = 0;
                }
                currentLine.erase(0, pos + delimiter.length());
            }

            //Getting y coordinate
            pos = currentLine.find(delimiter);

            if (pos != string::npos) {
                try {
                    y = stof(currentLine.substr(0, pos));
                } catch (...) {
                    cout << "Error while converting y into a float."
                         << "Setting to default value : 0."
                         << endl;
                    y = 0;
                }
            }

            //Log
            cout << "Getting coordinates of tower "
                 << index
                 << "("
                 << x
                 << ", "
                 << y
                 << ")"
                 << endl;

            //Pushing into the vector
            coordinates.push_back(Coordinates(x, y));
        }
    }

    return coordinates;
}