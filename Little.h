#ifndef TBP_LITTLE_LITTLE_H
#define TBP_LITTLE_LITTLE_H

#include <stack>
#include <limits>
#include <vector>
#include <iostream>
#include <fstream>

#include "LittleNode.h"
#include "Segment.h"
#include "Coordinates.h"

using namespace std;

class Little {
private:
    stack<LittleNode> nodes;
    vector<Segment> segments;
    double reference;
public:
    Little();

    virtual ~Little();

    const stack<LittleNode> & getNodes() const;

    void setNodes(const stack<LittleNode> &nodes);

    const vector<Segment> & getSegments() const;

    void setSegments(const vector<Segment> &segments);

    double getReference() const;

    void setReference(double reference);

    void start();

    void examineNode(LittleNode node);

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
    MatrixXd *getDistancesMatrix(vector<Coordinates> coordinates);
};


#endif //TBP_LITTLE_LITTLE_H
