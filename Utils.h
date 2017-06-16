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
 * Reduce a matrix row according to Little's algorithm
 * @param matrix the matrix to reduce
 * @param row the matrix's row index
 * @return the value reduced
 */
double reduceMatrixRow(MatrixXd *matrix, size_t row);

/**
 * Reduce a matrix column according to Little's algorithm
 * @param matrix the matrix to reduce
 * @param col the matrix's column index
 * @return the value reduced
 */
double reduceMatrixCol(MatrixXd *matrix, size_t col);

/**
 * Reduce all the matrix's row
 * @param matrix the matrix
 * @return the total amount reduced
 */
double reduceMatrixRows(MatrixXd *matrix);

/**
 * Reduce all the matrix's columns
 * @param matrix the matrix
 * @return the total amount reduced
 */
double reduceMatrixCols(MatrixXd *matrix);


#endif //TBP_LITTLE_UTILS_H
