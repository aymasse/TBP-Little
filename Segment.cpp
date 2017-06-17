#include "Segment.h"

Segment::Segment() {
    from = 0;
    to = 0;
}

Segment::Segment(long from, long to) : from(from), to(to) {}

long Segment::getFrom() const {
    return from;
}

void Segment::setFrom(long from) {
    Segment::from = from;
}

long Segment::getTo() const {
    return to;
}

void Segment::setTo(long to) {
    Segment::to = to;
}
