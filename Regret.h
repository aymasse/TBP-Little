#ifndef TBP_LITTLE_REGRET_H
#define TBP_LITTLE_REGRET_H

#include "Segment.h"

class Regret {
private:
    Segment segment;
    double value;
public:
    Regret();

    Regret(const Segment &segment, double value);

    virtual ~Regret();

    const Segment &getSegment() const;

    void setSegment(const Segment &segment);

    double getValue() const;

    void setValue(double value);
};


#endif //TBP_LITTLE_REGRET_H
