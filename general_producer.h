#ifndef GENERAL_PRODUCER_H
#define GENERAL_PRODUCER_H

#include "producer.h"

class General_Producer : public Producer {
public:
    General_Producer(Monitor* mon, int production_time);
    void produce();
};

#endif