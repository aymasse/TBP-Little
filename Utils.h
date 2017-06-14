#ifndef TBP_LITTLE_UTILS_H
#define TBP_LITTLE_UTILS_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "Coordinates.h"

using std::vector;
using std::string;
using std::ifstream;
using std::getline;
using std::stoi;
using std::stof;
using std::cout;
using std::endl;

/**
 * Return a vector of Coordinates containing the coordinates of all towers described inside fileName
 * @param fileName
 * @return a vector of coordinates
 */
vector<Coordinates> getCoordinates(string fileName);

#endif //TBP_LITTLE_UTILS_H
