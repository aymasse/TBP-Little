#ifndef TBP_LITTLE_LITTLE_H
#define TBP_LITTLE_LITTLE_H

#include <stack>
#include <limits>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

#include "LittleNode.h"
#include "Segment.h"
#include "Coordinates.h"

using namespace std;

typedef chrono::high_resolution_clock Clock;

class Little {
private:
    stack<LittleNode> nodes;
    vector<Segment> segments;
    double reference;
    MatrixXd *distanceMatrix;
    string fileName;
    size_t nbOfVisitedNodes;
public:
    Little();

    Little(const string &fileName);

    virtual ~Little();

    const stack<LittleNode> & getNodes() const;

    void setNodes(const stack<LittleNode> &nodes);

    const vector<Segment> & getSegments() const;

    void setSegments(const vector<Segment> &segments);

    double getReference() const;

    void setReference(double reference);

    MatrixXd *getDistanceMatrix() const;

    void setDistanceMatrix(MatrixXd *distanceMatrix);

    const string &getFileName() const;

    void setFileName(const string &fileName);

    /**
     * Satrt the algorithm
     */
    void start();

    /**
     * Sort the segments for better readability
     * 7-6, 8-7, 6-8 -> 7-6, 6-8, 8-7
     */
    void sortSegments();

    /**
     * Print the results of the algorithm
     */
    void printResults();

    /**
     * Examine the node
     * @param node
     */
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

    /**
     * Compute the maximum number of nodes the matrix size can create
     * @param nbRows the matrix's number of rows
     * @return the number of nodes this matrix can create at most
     */
    size_t computeMaxNumberOfNodes(size_t nbRows);
};


#endif //TBP_LITTLE_LITTLE_H
