#include "Regret.h"

Regret::Regret() {}

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
