#include "Regret.h"

Regret::Regret() {
    segment = Segment();
    value = numeric_limits<double>::max();
}


Regret::Regret(const Segment &segment) : segment(segment) {
    value = numeric_limits<double>::max();
}

Regret::Regret(const Segment &segment, double value) : segment(segment), value(value) {}

Regret::~Regret() {}

const Segment &Regret::getSegment() const {
    return segment;
}

void Regret::setSegment(const Segment &segment) {
    Regret::segment = segment;
}

double Regret::getValue() const {
    return value;
}

void Regret::setValue(double value) {
    Regret::value = value;
}

bool Regret::operator<(const Regret &rhs) const {
    return value < rhs.value;
}

bool Regret::operator>(const Regret &rhs) const {
    return rhs < *this;
}

bool Regret::operator<=(const Regret &rhs) const {
    return !(rhs < *this);
}

bool Regret::operator>=(const Regret &rhs) const {
    return !(*this < rhs);
}

