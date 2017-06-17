#include "LittleNode.h"

LittleNode::LittleNode() {
    matrix = nullptr;
    value = -1;
    parentValue = 0;
    segments = vector<Segment>();
}

LittleNode::LittleNode(MatrixXd *matrix) : matrix(matrix) {
    value = -1;
    parentValue = 0;
    segments = vector<Segment>();
}

LittleNode::LittleNode(MatrixXd *matrix, double parentValue, const vector<Segment> &segments) : matrix(matrix),
                                                                                                parentValue(
                                                                                                        parentValue),
                                                                                                segments(segments) {
    value = -1;
}

LittleNode::LittleNode(MatrixXd *matrix, double value, double parentValue, const vector<Segment> &segments) : matrix(
        matrix), value(value), parentValue(parentValue), segments(segments) {}

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

MatrixXd *LittleNode::getMatrix() const {
    return matrix;
}

void LittleNode::setMatrix(MatrixXd *matrix) {
    LittleNode::matrix = matrix;
}

double LittleNode::reduceMatrixRow(long row) {
    if (matrix->rows() < row || row < 0) {
        throw out_of_range("Provided row index is out of matrix bounds.");
    }

    double rowMin = getRowMin(row);

    for (size_t col = 0; col < matrix->cols(); ++col) {
        if ((*matrix)(row, col) >= 0) {
            (*matrix)(row, col) -= rowMin;
        }
    }

    return rowMin;
}

double LittleNode::reduceMatrixCol(long col) {
    if (matrix->cols() < col || col < 0) {
        throw out_of_range("Provided column index is out of matrix bounds.");
    }

    double colMin = getColMin(col);

    for (size_t row = 0; row < matrix->rows(); ++row) {
        if ((*matrix)(row, col) >= 0) {
            (*matrix)(row, col) -= colMin;
        }
    }

    return colMin;

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
    if (row > matrix->rows() || row < 0) {
        throw out_of_range("Provided row index is out of matrix range.");
    }

    for (size_t col = 0; col < matrix->cols(); ++col) {
        disableSegment(Segment(row, col));
    }
}

void LittleNode::removeMatrixCol(long col) {
    if (col > matrix->cols() || col < 0) {
        throw out_of_range("Provided column index is out of matrix range.");
    }

    for (size_t row = 0; row < matrix->rows(); ++row) {
        disableSegment(Segment(row, col));
    }
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
    if (matrix->row(segment.getFrom()).maxCoeff() < 0) {
        minRow = 0;
    } else {
        for (size_t col = 0; col < matrix->cols(); ++col) {
            if (col != segment.getTo()) {
                double value = (*matrix)(segment.getFrom(), col);
                if (value >= 0 && value < minRow) {
                    minRow = value;
                }
            }
        }
    }

    if (matrix->col(segment.getTo()).maxCoeff() < 0) {
        minCol = 0;
    } else {
        //Compute the minimal value in the specified column
        for (size_t row = 0; row < matrix->rows(); ++row) {
            if (row != segment.getFrom()) {
                double value = (*matrix)(row, segment.getTo());
                if (value >= 0 && value < minCol) {
                    minCol = (*matrix)(row, segment.getTo());
                }
            }
        }
    }

    regret.setValue(minRow + minCol);

    return regret;
}

void LittleNode::disableLoops() {
    vector<Segment> segmentToExamine = segments;
    vector<Loop> loops = vector<Loop>();

    if (segmentToExamine.size() > 0) {
        while (segmentToExamine.size() > 0) {
            bool found = false;

            for (size_t loopIndex = 0; loopIndex < loops.size(); ++loopIndex) {
                vector<Segment>::iterator it = segmentToExamine.begin();

                while (it != segmentToExamine.end()) {
                    bool match = false;

                    if (it->getTo() == loops.at(loopIndex).getStart()) {
                        vector<Segment> loopSegments = loops.at(loopIndex).getLoop();
                        loopSegments.insert(loopSegments.begin(), *it);
                        loops.at(loopIndex).setLoop(loopSegments);
                        match = true;
                        found = true;
                    }

                    if (it->getFrom() == loops.at(loopIndex).getEnd()) {
                        vector<Segment> loopSegments = loops.at(loopIndex).getLoop();
                        loopSegments.push_back(*it);
                        loops.at(loopIndex).setLoop(loopSegments);
                        match = true;
                        found = true;
                    }

                    if (match) {
                        segmentToExamine.erase(it);
                        it = segmentToExamine.begin();
                    } else {
                        ++it;
                    }
                }
            }

            if (!found) {
                Loop loop = Loop();
                vector<Segment> loopSegments = loop.getLoop();
                vector<Segment>::iterator it = segmentToExamine.begin();
                loopSegments.push_back(*it);
                segmentToExamine.erase(it);
                loop.setLoop(loopSegments);
                loops.push_back(loop);
            }
        }

        for (size_t loopIndex = 0; loopIndex < loops.size(); ++loopIndex) {
            Segment closing = loops.at(loopIndex).computeClosing();
            disableSegment(closing);
//            cout << "Disabling "
//                 << closing
//                 << " for loop "
//                 << loops.at(loopIndex)
//                 << endl;
        }
    }
}

double LittleNode::getRowMin(long row) {
    double rowMin = numeric_limits<double>::max();

    if (row > matrix->rows() || row < 0) {
        throw out_of_range("Provided row index is out of matrix's bounds.");
    }

    if (matrix->row(row).maxCoeff() < 0) {
        return 0;
    }

    for (int col = 0; col < matrix->cols(); ++col) {
        double value = matrix->row(row)(0, col);
        if (value >= 0 && value < rowMin) {
            rowMin = value;
        }
    }

    return rowMin;
}

double LittleNode::getColMin(long col) {
    double colMin = numeric_limits<double>::max();

    if (col > matrix->cols() || col < 0) {
        throw out_of_range("Provided column index is out of matrix's bounds.");
    }

    if (matrix->col(col).maxCoeff() < 0) {
        return 0;
    }

    for (int row = 0; row < matrix->rows(); ++row) {
        double value = matrix->col(col)(row, 0);
        if (value >= 0 && value < colMin) {
            colMin = value;
        }
    }

    return colMin;
}

void LittleNode::disableSegment(Segment segment) {
    long from = segment.getFrom();
    long to = segment.getTo();

    if (from < 0 || from > matrix->rows() || to < 0 || to > matrix->cols()) {
        throw out_of_range("Provided segment is not in the matrix.");
    }

    if ((*matrix)(segment.getFrom(), segment.getTo()) != -1) {
        (*matrix)(segment.getFrom(), segment.getTo()) = -1;
//        cout << "Disabling segment "
//             << segment
//             << endl;
    }
}

double LittleNode::getParentValue() const {
    return parentValue;
}

void LittleNode::setParentValue(double parentValue) {
    LittleNode::parentValue = parentValue;
}

LittleNode::~LittleNode() {
//    delete matrix;
}

