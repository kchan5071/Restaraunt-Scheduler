#ifndef PRODUCER_H
#define PRODUCER_H

#include "monitor.h"
#include "seating.h"


class Producer {
protected:
    Monitor* mon;
    RequestType type;
    int production_time;

public:
    Producer(Monitor* mon, int production_time, RequestType type);

    void produce();

    static void* start_produce(void* arg);
};
#endif