#ifndef PRODUCER_H
#define PRODUCER_H

#include "monitor.h"
#include "seating.h"
#include "log_helper.h"

class Producer {
protected:
    Monitor* mon;
    RequestType type;
    int production_time;
    Log_Helper* log_helper;

public:
    Producer(Monitor* mon, Log_Helper* log_helper, int production_time, RequestType type);

    void produce();

    static void* start_produce(void* arg);
};
#endif