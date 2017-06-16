#ifndef TBP_LITTLE_LITTLE_H
#define TBP_LITTLE_LITTLE_H

#include <stack>
#include <limits>

#include "LittleNode.h"
#include "Segment.h"

using namespace std;

class Little {
private:
    stack<LittleNode> nodes;
    stack<Segment> segments;
    double reference;
public:
    Little();

    virtual ~Little();

    const stack<LittleNode> &getNodes() const;

    void setNodes(const stack<LittleNode> &nodes);

    const stack<Segment> &getSegments() const;

    void setSegments(const stack<Segment> &segments);

    double getReference() const;

    void setReference(double reference);
};


#endif //TBP_LITTLE_LITTLE_H
