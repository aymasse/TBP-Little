#ifndef TBP_LITTLE_UTILS_H
#define TBP_LITTLE_UTILS_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <exception>

#include "Coordinates.h"
#include "Eigen/Core"

using namespace std;
using namespace Eigen;

/**
 * Return a vector of Coordinates containing the coordinates of all towers described inside fileName
 * @param fileName
 * @return a vector of coordinates
 */
vector<Coordinates> getCoordinates(string fileName);

/**
 * Return the matrix of distances between all points
 * @param coordinates a vector of coordinates
 * @return A matrix of doubles
 */
Matrix<double, Dynamic, Dynamic> getDistancesMatrix(vector<Coordinates> coordinates);

#endif //TBP_LITTLE_UTILS_H
