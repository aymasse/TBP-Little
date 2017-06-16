#include "Little.h"

Little::Little() {
    nodes = stack<LittleNode>();
    segments = vector<Segment>();
    reference = numeric_limits<double>::max();
}

Little::~Little() {}

const stack<LittleNode> &Little::getNodes() const {
    return nodes;
}

void Little::setNodes(const stack<LittleNode> &nodes) {
    Little::nodes = nodes;
}

double Little::getReference() const {
    return reference;
}

void Little::setReference(double reference) {
    Little::reference = reference;
}

const vector<Segment> &Little::getSegments() const {
    return segments;
}

void Little::setSegments(const vector<Segment> &segments) {
    Little::segments = segments;
}

void Little::start() {
    nodes.push(LittleNode(getDistancesMatrix(getCoordinates("ville.txt"))));

    while (nodes.size() > 0) {
        LittleNode currentNode = nodes.top();
        nodes.pop();

        double currentNodeValue = currentNode.getValue();

        if (currentNodeValue > 0) {
            //Node with a value already

            if (currentNodeValue < getReference()) {
                //TODO exclusion
            }
        } else {
            //Node to examine
            examineNode(currentNode);
        }
    }
}

void Little::examineNode(LittleNode node) {
    if (node.getMatrix()->size() > 4) {
        //Not last node
        node.setValue(reduceMatrix(node.getMatrix()));
        //TODO
    } else {
        //Last node

    }
}
