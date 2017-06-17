#ifndef TBP_LITTLE_LITTLENODE_H
#define TBP_LITTLE_LITTLENODE_H

#include <vector>
#include <exception>
#include <limits>

#include "Eigen/Core"
#include "Segment.h"
#include "Regret.h"

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

    LittleNode(MatrixXd *matrix, const vector<Segment> &segments);

    LittleNode(MatrixXd *matrix, double value, const vector<Segment> &segments);

    MatrixXd *getMatrix() const;

    void setMatrix(MatrixXd *matrix);

    double getValue() const;

    void setValue(double value);

    const vector<Segment> & getSegments() const;

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
    void removeMatrixRow(long row);

    /**
     * Remove a column from the matrix
     * @param col the column index
     */
    void removeMatrixCol(long col);

    /**
     * Return the maximal regret
     * @return the maximal regret
     */
    Regret getMaxRegret();

    /**
     * Return a list of regrets
     * @return a list of regrets
     */
    vector<Regret> getRegrets();

    /**
     * Return a list of segment containing 0
     * @return a list of segments containing 0
     */
    vector<Segment> getRegretsSegments();

    /**
     * Compute a regret at the given segment
     * @param segment
     * @return a regret
     */
    Regret computeRegret(Segment segment);
};


#endif //TBP_LITTLE_LITTLENODE_H
