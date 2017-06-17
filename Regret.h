#ifndef TBP_LITTLE_REGRET_H
#define TBP_LITTLE_REGRET_H

#include <limits>

#include "Segment.h"

using namespace std;

class Regret {
private:
    Segment segment;
    double value;
public:
    Regret();

    Regret(const Segment &segment);

    Regret(const Segment &segment, double value);

    virtual ~Regret();

    const Segment &getSegment() const;

    void setSegment(const Segment &segment);

    double getValue() const;

    void setValue(double value);

    bool operator<(const Regret &rhs) const;

    bool operator>(const Regret &rhs) const;

    bool operator<=(const Regret &rhs) const;

    bool operator>=(const Regret &rhs) const;

};


#endif //TBP_LITTLE_REGRET_H
