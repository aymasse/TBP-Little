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

    /**
     * Reduce a matrix row according to Little's algorithm
     * @param matrix the matrix to reduce
     * @param row the matrix's row index
     * @return the value reduced
     */
    double reduceMatrixRow(size_t row);

    /**
     * Reduce a matrix column according to Little's algorithm
     * @param matrix the matrix to reduce
     * @param col the matrix's column index
     * @return the value reduced
     */
    double reduceMatrixCol(size_t col);

    /**
     * Reduce all the matrix's row
     * @param matrix the matrix
     * @return the total amount reduced
     */
    double reduceMatrixRows();

    /**
     * Reduce all the matrix's columns
     * @param matrix the matrix
     * @return the total amount reduced
     */
    double reduceMatrixCols();

    /**
     * Reduce the matrix rows and columns
     * @param matrix the matrix
     * @return the total amount reduced
     */
    double reduceMatrix();

    /**
     * Remove a row from the matrix
     * @param row the row index
     */
    void removeMatrixRow(size_t row);

    /**
     * Remove a column from the matrix
     * @param col the column index
     */
    void removeMatrixCol(size_t col);
};


#endif //TBP_LITTLE_LITTLENODE_H
