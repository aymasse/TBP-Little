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

std::ostream &operator<<(std::ostream &os, const Segment &segment) {
    os << "from: " << segment.from << " to: " << segment.to;
    return os;
}

Segment Segment::inverse() {
    return Segment(to, from);
}
