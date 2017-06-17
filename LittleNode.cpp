#include "LittleNode.h"

LittleNode::LittleNode() {
    matrix = nullptr;
    value = -1;
    segments = vector<Segment>();
}

LittleNode::LittleNode(MatrixXd *matrix) : matrix(matrix) {
    value = -1;
    segments = vector<Segment>();
}

LittleNode::LittleNode(MatrixXd *matrix, const vector<Segment> &segments) : matrix(matrix), segments(segments) {
    value = -1;
}

LittleNode::LittleNode(MatrixXd *matrix, double value, const vector<Segment> &segments) : matrix(matrix), value(value),
                                                                                          segments(segments) {}

double LittleNode::getValue() const {
    return value;
}

void LittleNode::setValue(double value) {
    LittleNode::value = value;
}

const vector<Segment> & LittleNode::getSegments() const {
    return segments;
}

void LittleNode::setSegments(const vector<Segment> &segments) {
    LittleNode::segments = segments;
}

MatrixXd *LittleNode::getMatrix() const {
    return matrix;
}

void LittleNode::setMatrix(MatrixXd *matrix) {
    LittleNode::matrix = matrix;
}

double LittleNode::reduceMatrixRow(size_t row) {
    if (matrix->rows() > row || row < 0) {
        double rowMin = matrix->row(row).minCoeff();

        for (size_t col = 0; col < matrix->cols(); ++col) {
            (*matrix)(row, col) -= rowMin;
        }

        return rowMin;
    } else {
        throw out_of_range("Provided row index is out of matrix bounds.");
    }
}

double LittleNode::reduceMatrixCol(size_t col) {
    if (matrix->cols() > col || col < 0) {
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

    if (row > nbRows || row < 0) {
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

    if (col > nbCols || col < 0) {
        throw out_of_range("Provided column index is out of matrix range.");
    }

    if (col < nbCols) {
        matrix->block(0, col, nbRows, nbCols - col) = matrix->block(0, col + 1, nbRows, nbCols - col);
    }

    matrix->conservativeResize(nbRows, nbCols);
}

Regret LittleNode::getMaxRegret() {
    vector<Regret> regrets = getRegrets();
    stable_sort(regrets.begin(), regrets.end());
    return regrets.back();
}

vector<Regret> LittleNode::getRegrets() {
    vector<Regret> regrets = vector<Regret>();
    vector<Segment> regretsSegments = getRegretsSegments();

    for (Segment regretSegment : regretsSegments) {
        regrets.push_back(computeRegret(regretSegment));
    }

    return regrets;
}

vector<Segment> LittleNode::getRegretsSegments() {
    vector<Segment> segments = vector<Segment>();

    for (size_t row = 0; row < matrix->rows(); ++row) {
        for (size_t col = 0; col < matrix->cols(); ++col) {
            if ((*matrix)(row, col) == 0) {
                segments.push_back(Segment(row, col));
            }
        }
    }

    return segments;
}

Regret LittleNode::computeRegret(Segment segment) {
    Regret regret = Regret(segment);
    double minRow = numeric_limits<double>::max();
    double minCol = numeric_limits<double>::max();

    if ((*matrix)(segment.getFrom(), segment.getTo()) != 0) {
        throw invalid_argument("Given segment is not equals to 0.");
    }

    //Compute the minimal value in the specified row
    for (size_t col = 0; col < matrix->cols(); ++col) {
        if (col != segment.getTo()) {
            if ((*matrix)(segment.getFrom(), col) < minRow) {
                minRow = (*matrix)(segment.getFrom(), col);
            }
        }
    }

    //Compute the minimal value in the specified column
    for (size_t row = 0; row < matrix->rows(); ++row) {
        if (row != segment.getFrom()) {
            if ((*matrix)(row, segment.getTo()) < minCol) {
                minCol = (*matrix)(row, segment.getTo());
            }
        }
    }

    regret.setValue(minRow + minCol);

    return regret;
}

