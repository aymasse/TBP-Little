#include "Little.h"

Little::Little() {
    nodes = stack<LittleNode>();
    segments = vector<Segment>();
    reference = numeric_limits<double>::max();
    fileName = "";
    nbOfVisitedNodes = 0;
}

Little::Little(const string &fileName) : fileName(fileName) {
    nodes = stack<LittleNode>();
    segments = vector<Segment>();
    reference = numeric_limits<double>::max();
    nbOfVisitedNodes = 0;
}

Little::~Little() {
    delete distanceMatrix;
}

const stack<LittleNode> &Little::getNodes() const {
    return nodes;
}

void Little::setNodes(const stack<LittleNode> &nodes) {
    Little::nodes = nodes;
}

double Little::getReference() const {
    return reference;
}

void Little::setReference(double reference) {
    Little::reference = reference;
}

const vector<Segment> &Little::getSegments() const {
    return segments;
}

void Little::setSegments(const vector<Segment> &segments) {
    Little::segments = segments;
}

void Little::start() {
    auto start = Clock::now();

    distanceMatrix = getDistancesMatrix(getCoordinates(fileName));

    nodes.push(LittleNode(new MatrixXd(*distanceMatrix)));


    while (nodes.size() > 0) {
        LittleNode currentNode = nodes.top();
        nodes.pop();
        nbOfVisitedNodes++;

        double currentNodeValue = currentNode.getValue();

//        cout << "Node value: " << currentNodeValue << endl;
//        cout << "Reference :" << reference << endl;

        if (currentNodeValue < reference) {
            examineNode(currentNode);
        }

        delete currentNode.getMatrix();
    }

    sortSegments();
    printResults();

    auto finish = Clock::now();

    cout << "Algorithm executed in "
         << chrono::duration_cast<chrono::seconds>(finish - start).count()
         << " seconds."
         << endl;
}

void Little::examineNode(LittleNode node) {
    node.disableLoops();

    double reducedAmount = node.reduceMatrix();
    double newValue = reducedAmount + node.getParentValue();

    node.setValue(newValue);

    if (newValue < reference) {
        if (node.getMatrix()->rows() - node.getSegments().size() > 2) {
            //Not last node
            Regret maxRegret = node.getMaxRegret();

            //Include path matrix
            MatrixXd *includeMatrix = new MatrixXd(*node.getMatrix());
            LittleNode includeNode = LittleNode(includeMatrix, node.getValue(), node.getSegments());

            //Push new segment
            vector<Segment> newNodeSegments = includeNode.getSegments();
            newNodeSegments.push_back(maxRegret.getSegment());
            includeNode.setSegments(newNodeSegments);

            //Remove depart row and finish column
            includeNode.removeMatrixRow(maxRegret.getSegment().getFrom());
            includeNode.removeMatrixCol(maxRegret.getSegment().getTo());

            //Exclude path matrix
            MatrixXd *excludeMatrix = new MatrixXd(*node.getMatrix());

            //Disable the segment on the new matrix
            LittleNode excludeNode = LittleNode(excludeMatrix, node.getValue() + maxRegret.getValue(), node.getValue(),
                                                node.getSegments());
            excludeNode.disableSegment(maxRegret.getSegment()); //Disable excluded segment


            //Push exclude node
            nodes.push(excludeNode);
            //Push include node
            nodes.push(includeNode);
        } else {
            //Last node
            segments = node.getSegments();

            //Only 2 segments left to include
            for (size_t row = 0; row < node.getMatrix()->rows(); ++row) {
                for (int col = 0; col < node.getMatrix()->cols(); ++col) {
                    if ((*node.getMatrix())(row, col) >= 0) {
                        segments.push_back(Segment(row, col));
                    }
                }
            }

            reference = node.getValue();
        }
    }
}

vector<Coordinates> Little::getCoordinates(string fileName) {
    vector<Coordinates> coordinates = vector<Coordinates>();
    string currentLine;
    ifstream file(fileName);
    string delimiter = " ";

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
             << " ("
             << x
             << ", "
             << y
             << ")"
             << endl;

        //Pushing into the vector
        coordinates.push_back(Coordinates(x, y));
    }

    return coordinates;
}

MatrixXd *Little::getDistancesMatrix(vector<Coordinates> coordinates) {
    MatrixXd *matrix = new MatrixXd();
    size_t numberOfPoints = coordinates.size();

    matrix->resize(numberOfPoints, numberOfPoints);

    //Filling the matrix
    for (size_t row = 0; row < numberOfPoints; ++row) {
        for (size_t column = 0; column < numberOfPoints; ++column) {
            if (row != column) {
                (*matrix)(row, column) = coordinates[row].computeDistanceWith(coordinates[column]);
            } else {
                //The distance from a point to itself is set to max value
                (*matrix)(row, column) = -1;
            }
        }
    }

    return matrix;
}

void Little::printResults() {
    double totalDistance = 0;

    cout << "Optimal path : " << endl;

    for (vector<Segment>::iterator iterator = segments.begin(); iterator < segments.end(); ++iterator) {
        long from = iterator->getFrom();
        long to = iterator->getTo();
        cout << "From "
             << from + 1
             << " to "
             << to + 1
             << " for a distance of "
             << (*distanceMatrix)(from, to)
             << endl;

        totalDistance += (*distanceMatrix)(from, to);
    }

    cout << "Total cost: "
         << totalDistance
         << endl;
    cout << "Number of visited nodes: "
         << nbOfVisitedNodes
         << " of "
         << computeMaxNumberOfNodes(distanceMatrix->rows())
         << " maximum nodes."
         << endl;
}

void Little::sortSegments() {
    vector<Segment> sortedSegments = vector<Segment>();
    vector<Segment> segmentsToSort = segments;

    for (vector<Segment>::iterator iterator = segmentsToSort.begin(); iterator < segmentsToSort.end(); ++iterator) {
        if (iterator->getFrom() == 0) {
            sortedSegments.push_back(*iterator);
            segmentsToSort.erase(iterator);
            break;
        }
    }

    while (segmentsToSort.size() > 0) {
        for (vector<Segment>::iterator iterator = segmentsToSort.begin(); iterator < segmentsToSort.end(); ++iterator) {
            if (iterator->getFrom() == sortedSegments.back().getTo()) {
                sortedSegments.push_back(*iterator);
                segmentsToSort.erase(iterator);
                break;
            }

            if (iterator->getTo() == sortedSegments.front().getFrom()) {
                sortedSegments.insert(sortedSegments.begin(), *iterator);
                segmentsToSort.erase(iterator);
                break;
            }
        }
    }

    segments = sortedSegments;
}

MatrixXd *Little::getDistanceMatrix() const {
    return distanceMatrix;
}

void Little::setDistanceMatrix(MatrixXd *distanceMatrix) {
    Little::distanceMatrix = distanceMatrix;
}

const string &Little::getFileName() const {
    return fileName;
}

void Little::setFileName(const string &fileName) {
    Little::fileName = fileName;
}

size_t Little::computeMaxNumberOfNodes(size_t nbRows) {
    if (nbRows == 3) {
        return 8;
    } else {
        return (nbRows - 1) * (1 + computeMaxNumberOfNodes(nbRows - 1));
    }
}

