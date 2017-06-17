#include "Loop.h"

Loop::Loop() {
    loop = vector<Segment>();
}

const vector<Segment> &Loop::getLoop() const {
    return loop;
}

void Loop::setLoop(const vector<Segment> &loop) {
    Loop::loop = loop;
}

Segment Loop::computeClosing() {
    return Segment(getEnd(), getStart());
}

long Loop::getEnd() {
    if (loop.size() == 0) {
        throw logic_error("Loop is empty.");
    }

    return loop.back().getTo();
}

long Loop::getStart() {
    if (loop.size() == 0) {
        throw logic_error("Loop is empty.");
    }

    return loop.front().getFrom();
}

ostream &operator<<(ostream &os, const Loop &loop) {
    os << "Loop: ";

    for (Segment segment : loop.getLoop()) {
        os << segment.getFrom()
           << " - "
           << segment.getTo()
           << ", ";
    }

    os << endl;

    return os;
}
