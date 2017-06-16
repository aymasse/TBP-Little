#include "LittleNode.h"

LittleNode::LittleNode() {}

double LittleNode::getValue() const {
    return value;
}

void LittleNode::setValue(double value) {
    LittleNode::value = value;
}

const vector<Segment> &LittleNode::getSegments() const {
    return segments;
}

void LittleNode::setSegments(const vector<Segment> &segments) {
    LittleNode::segments = segments;
}

LittleNode::LittleNode(MatrixXd *matrix) : matrix(matrix) {
    value = -1;
    segments = vector<Segment>();
}

LittleNode::LittleNode(MatrixXd *matrix, double value, const vector<Segment> &segments) : matrix(matrix), value(value),
                                                                                          segments(segments) {}

MatrixXd *LittleNode::getMatrix() const {
    return matrix;
}

void LittleNode::setMatrix(MatrixXd *matrix) {
    LittleNode::matrix = matrix;
}

