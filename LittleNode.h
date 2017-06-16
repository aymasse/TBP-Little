#ifndef TBP_LITTLE_LITTLENODE_H
#define TBP_LITTLE_LITTLENODE_H

#include "Eigen/Core"

using namespace Eigen;


class LittleNode {
private:
    MatrixXd matrix;
    double value;
    LittleNode *exclude;
    LittleNode *include;
    LittleNode *parent;
public:
    LittleNode();

    LittleNode(const MatrixXd &matrix);

    LittleNode(const MatrixXd &matrix, LittleNode *parent);

    const MatrixXd &getMatrix() const;

    void setMatrix(const MatrixXd &matrix);

    double getValue() const;

    void setValue(double value);

    LittleNode *getExclude() const;

    void setExclude(LittleNode *exclude);

    LittleNode *getInclude() const;

    void setInclude(LittleNode *include);

    LittleNode *getParent() const;

    void setParent(LittleNode *parent);
};


#endif //TBP_LITTLE_LITTLENODE_H
