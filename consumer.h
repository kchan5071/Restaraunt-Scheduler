#ifndef CONSUMER_H
#define CONSUMER_H

#include "monitor.h"

class Consumer {
protected:
    Monitor* mon;
    std::string type;
    int consumption_time;


public:
    Consumer(Monitor* mon, int consumption_time, std::string type);

    void consume();

    static void* start_consume(void* arg);
};
#endif