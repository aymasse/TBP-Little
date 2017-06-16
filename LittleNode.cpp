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

double LittleNode::reduceMatrixRow(long row) {
    if (matrix->rows() > row) {
        double rowMin = matrix->row(row).minCoeff();

        for (size_t col = 0; col < matrix->cols(); ++col) {
            (*matrix)(row, col) -= rowMin;
        }

        return rowMin;
    } else {
        throw out_of_range("Provided row index is out of matrix bounds.");
    }
}

double LittleNode::reduceMatrixCol(long col) {
    if (matrix->cols() > col) {
        double colMin = matrix->col(col).minCoeff();

        for (size_t row = 0; row < matrix->rows(); ++row) {
            (*matrix)(row, col) -= colMin;
        }

        return colMin;
    } else {
        throw out_of_range("Provided column index is out of matrix bounds.");
    }
}

double LittleNode::reduceMatrixRows() {
    double reducedSum = 0;

    for (size_t row = 0; row < matrix->rows(); ++row) {
        reducedSum += reduceMatrixRow(row);
    }

    return reducedSum;
}

double LittleNode::reduceMatrixCols() {
    double reducedSum = 0;

    for (size_t col = 0; col < matrix->rows(); ++col) {
        reducedSum += reduceMatrixCol(col);
    }

    return reducedSum;
}

double LittleNode::reduceMatrix() {
    double reducedSum = 0;

    reducedSum += reduceMatrixRows();
    reducedSum += reduceMatrixCols();

    return reducedSum;
}

void LittleNode::removeMatrixRow(long row) {
    long nbRows = matrix->rows() - 1;
    long nbCols = matrix->cols();

    if (row > nbRows) {
        throw out_of_range("Provided row index is out of matrix range.");
    }

    if (row < nbRows) {
        matrix->block(row, 0, nbRows - row, nbCols) = matrix->block(row + 1, 0, nbRows - row, nbCols);
    }

    matrix->conservativeResize(nbRows, nbCols);
}

void LittleNode::removeMatrixCol(long col) {
    long nbRows = matrix->rows();
    long nbCols = matrix->cols() - 1;

    if (col > nbCols) {
        throw out_of_range("Provided column index is out of matrix range.");
    }

    if (col < nbCols) {
        matrix->block(0, col, nbRows, nbCols - col) = matrix->block(0, col + 1, nbRows, nbCols - col);
    }

    matrix->conservativeResize(nbRows, nbCols);
}

