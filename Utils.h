#ifndef TBP_LITTLE_UTILS_H
#define TBP_LITTLE_UTILS_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <exception>
#include <limits>

#include "Coordinates.h"
#include "Eigen/Core"

using namespace std;
using namespace Eigen;

/**
 * Return a vector of Coordinates containing the coordinates of all towers described inside fileName
 * @param fileName the name of the file containing all the points coordinates
 * @return a vector of coordinates
 */
vector<Coordinates> getCoordinates(string fileName);

/**
 * Return the matrix of distances between all points
 * @param coordinates a vector of coordinates
 * @return A matrix of doubles
 */
MatrixXd getDistancesMatrix(vector<Coordinates> coordinates);

/**
 * Return the lowest value of the specified row
 * @param matrix matrix
 * @param row row index
 * @return the lowest value of the row
 */
double getMatrixRowMin(MatrixXd matrix, size_t row);

/**
 * Return the lowest value of the specified column
 * @param matrix matrix
 * @param column column index
 * @return the lowest value of the column
 */
double getMatrixColumnMin(MatrixXd matrix, size_t column);

#endif //TBP_LITTLE_UTILS_H
