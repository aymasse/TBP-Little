#include "LittleNode.h"

LittleNode::LittleNode() {}

double LittleNode::getValue() const {
    return value;
}

void LittleNode::setValue(double value) {
    LittleNode::value = value;
}

LittleNode *LittleNode::getExclude() const {
    return exclude;
}

void LittleNode::setExclude(LittleNode *exclude) {
    LittleNode::exclude = exclude;
}

LittleNode *LittleNode::getInclude() const {
    return include;
}

void LittleNode::setInclude(LittleNode *include) {
    LittleNode::include = include;
}

LittleNode *LittleNode::getParent() const {
    return parent;
}

void LittleNode::setParent(LittleNode *parent) {
    LittleNode::parent = parent;
}

const MatrixXd &LittleNode::getMatrix() const {
    return matrix;
}

void LittleNode::setMatrix(const MatrixXd &matrix) {
    LittleNode::matrix = matrix;
}

LittleNode::LittleNode(const MatrixXd &matrix) : matrix(matrix) {}

LittleNode::LittleNode(const MatrixXd &matrix, LittleNode *parent) : matrix(matrix), parent(parent) {}
