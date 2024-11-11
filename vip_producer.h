#ifndef VIP_PRODUCER_H
#define VIP_PRODUCER_H

#include "producer.h"

class VIP_Producer : public Producer {
public:
    VIP_Producer(Monitor* mon, int production_time);
    void produce();
};

#endif
