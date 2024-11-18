#ifndef CONSUMER_H
#define CONSUMER_H

#include "monitor.h"
#include "seating.h"
#include <thread>
#include <chrono>

class Consumer
{
protected:
    Monitor *mon;
    Consumers type;
    int consumption_time;

public:
    Consumer(Monitor *mon, int consumption_time, Consumers type);

    void consume();
    static void *start_consume(void *arg);
};
#endif