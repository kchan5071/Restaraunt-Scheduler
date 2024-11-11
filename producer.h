#ifndef PRODUCER_H
#define PRODUCER_H

#include "monitor.h"


class Producer {
protected:
    Monitor* mon;
    std::string type;
    int production_time;

public:
    Producer(Monitor* mon, int production_time, std::string type);

    void produce();

    static void* start_produce(void* arg);
};
#endif