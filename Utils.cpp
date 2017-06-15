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
    } else {
        throw ios_base::failure("Error while opening " + fileName);
    }

    return coordinates;
}

MatrixXd getDistancesMatrix(vector<Coordinates> coordinates) {
    MatrixXd matrix = MatrixXd();
    size_t numberOfPoints = coordinates.size();

    matrix.resize(numberOfPoints, numberOfPoints);

    //Filling the matrix
    for (size_t row = 0; row < numberOfPoints; ++row) {
        for (size_t column = 0; column < numberOfPoints; ++column) {
            if (row != column) {
                matrix(row, column) = coordinates[row].computeDistanceWith(coordinates[column]);
            } else {
                //The distance from a point to itself is set to max value
                matrix(row, column) = numeric_limits<double>::max();
            }
        }
    }

    return matrix;
}

double getMatrixRowMin(MatrixXd matrix, size_t row) {
    double rowMin = 0;

    if (matrix.rows() > row) {
        rowMin = matrix.block(1, matrix.cols(), row, 0).minCoeff();
    } else {
        throw out_of_range("Given row index is out of matrix bounds.");
    }

    return rowMin;
}

double getMatrixColumnMin(MatrixXd matrix, size_t column) {
    double columnMin = 0;

    if (matrix.cols() > column) {
        columnMin = matrix.block(matrix.cols(), 1, 0, column).minCoeff();
    } else {
        throw out_of_range("Given column index is out of matrix bounds.");
    }

    return columnMin;
}
