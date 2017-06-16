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

double reduceMatrixRow(MatrixXd *matrix, size_t row) {
    if (matrix->rows() > row) {
        double rowMin = matrix->row(row).minCoeff();

        for (size_t col = 0; col < matrix->cols(); ++col) {
            (*matrix)(row, col) -= rowMin;
        }

        return rowMin;
    } else {
        throw out_of_range("Provided row index is out of matrix bounds.");
    }
}

double reduceMatrixCol(MatrixXd *matrix, size_t col) {
    if (matrix->cols() > col) {
        double colMin = matrix->col(col).minCoeff();

        for (size_t row = 0; row < matrix->rows(); ++row) {
            (*matrix)(row, col) -= colMin;
        }

        return colMin;
    } else {
        throw out_of_range("Provided column index is out of matrix bounds.");
    }
}

double reduceMatrixRows(MatrixXd *matrix) {
    double reducedSum = 0;

    for (size_t row = 0; row < matrix->rows(); ++row) {
        reducedSum += reduceMatrixRow(matrix, row);
    }

    return reducedSum;
}

double reduceMatrixCols(MatrixXd *matrix) {
    double reducedSum = 0;

    for (size_t col = 0; col < matrix->rows(); ++col) {
        reducedSum += reduceMatrixCol(matrix, col);
    }

    return reducedSum;
}
