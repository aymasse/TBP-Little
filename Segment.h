#ifndef TBP_LITTLE_SEGMENT_H
#define TBP_LITTLE_SEGMENT_H

#include <ostream>

class Segment {
private:
    long from;
    long to;
public:
    Segment();

    Segment(long from, long to);

    long getFrom() const;

    void setFrom(long from);

    long getTo() const;

    void setTo(long to);

    friend std::ostream &operator<<(std::ostream &os, const Segment &segment);

    Segment inverse();
};


#endif //TBP_LITTLE_SEGMENT_H
