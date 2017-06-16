#ifndef TBP_LITTLE_LITTLE_H
#define TBP_LITTLE_LITTLE_H

#include <stack>
#include <limits>
#include <vector>

#include "LittleNode.h"
#include "Segment.h"
#include "Utils.h"

using namespace std;

class Little {
private:
    stack<LittleNode> nodes;
    vector<Segment> segments;
    double reference;
public:
    Little();

    virtual ~Little();

    const stack<LittleNode> &getNodes() const;

    void setNodes(const stack<LittleNode> &nodes);

    const vector<Segment> &getSegments() const;

    void setSegments(const vector<Segment> &segments);

    double getReference() const;

    void setReference(double reference);

    void start();

    void examineNode(LittleNode node);
};


#endif //TBP_LITTLE_LITTLE_H
