#ifndef CONSUMER_H
#define CONSUMER_H

#include "monitor.h"
#include "seating.h"
#include "log_helper.h"
#include <thread>
#include <chrono>

class Consumer
{
protected:
    Monitor *mon;
    Consumers type;
    int consumption_time;
    Log_Helper *log_helper;

public:
    Consumer(Monitor *mon, Log_Helper *log_helper, int consumption_time, Consumers type);

    void consume();
    static void *start_consume(void *arg);
};
#endif