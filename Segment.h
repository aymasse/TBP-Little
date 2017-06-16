#ifndef TBP_LITTLE_SEGMENT_H
#define TBP_LITTLE_SEGMENT_H


class Segment {
private:
    int from;
    int to;
public:
    Segment();

    Segment(int from, int to);

    int getFrom() const;

    void setFrom(int from);

    int getTo() const;

    void setTo(int to);
};


#endif //TBP_LITTLE_SEGMENT_H
