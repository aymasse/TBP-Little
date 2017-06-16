#include "Little.h"

Little::Little() {
    nodes = stack<LittleNode>();
    segments = stack<Segment>();
    reference = numeric_limits<double>::max();
}

Little::~Little() {}

const stack<LittleNode> &Little::getNodes() const {
    return nodes;
}

void Little::setNodes(const stack<LittleNode> &nodes) {
    Little::nodes = nodes;
}

const stack<Segment> &Little::getSegments() const {
    return segments;
}

void Little::setSegments(const stack<Segment> &segments) {
    Little::segments = segments;
}

double Little::getReference() const {
    return reference;
}

void Little::setReference(double reference) {
    Little::reference = reference;
}
