#include "Segment.h"

Segment::Segment() {}

Segment::Segment(int from, int to) : from(from), to(to) {}

int Segment::getFrom() const {
    return from;
}

void Segment::setFrom(int from) {
    Segment::from = from;
}

int Segment::getTo() const {
    return to;
}

void Segment::setTo(int to) {
    Segment::to = to;
}
