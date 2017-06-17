#ifndef TBP_LITTLE_LOOP_H
#define TBP_LITTLE_LOOP_H

#include <vector>
#include <ostream>

#include "Segment.h"

using namespace std;

class Loop {
private:
    vector<Segment> loop;
public:
    Loop();

    const vector<Segment> &getLoop() const;

    void setLoop(const vector<Segment> &loop);

    Segment computeClosing();

    long getEnd();

    long getStart();

    friend ostream &operator<<(ostream &os, const Loop &loop);
};


#endif //TBP_LITTLE_LOOP_H
