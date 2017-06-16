#ifndef TBP_LITTLE_LITTLENODE_H
#define TBP_LITTLE_LITTLENODE_H

#include <vector>

#include "Eigen/Core"
#include "Segment.h"

using namespace Eigen;
using namespace std;

class LittleNode {
private:
    MatrixXd *matrix;
    double value;
    vector<Segment> segments;
public:
    LittleNode();

    LittleNode(MatrixXd *matrix);

    LittleNode(MatrixXd *matrix, double value, const vector<Segment> &segments);

    MatrixXd *getMatrix() const;

    void setMatrix(MatrixXd *matrix);

    double getValue() const;

    void setValue(double value);

    const vector<Segment> &getSegments() const;

    void setSegments(const vector<Segment> &segments);
};


#endif //TBP_LITTLE_LITTLENODE_H
