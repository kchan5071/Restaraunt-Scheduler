#ifndef CONSUMER_H
#define CONSUMER_H

#include "monitor.h"
#include "seating.h"
#include <thread>
#include <chrono>

/**
 * @brief   Class to represent a consumer
 */
class Consumer {
private:
    Monitor *mon;
    Consumers type;
    int consumption_time;

public:
    /**
     * @brief   Constructor for the Consumer class
     * 
     * @param mon               The monitor to consume from
     * @param consumption_time  The time to consume an item
     * @param type              The type of consumer
     */
    Consumer(Monitor *mon, int consumption_time, Consumers type);

    /**
     * @brief   Consume items from the monitor
     */
    void consume();

    /**
     * @brief   Start the consume function
     * 
     * @param arg   The consumer object
     * @return void* 
     */
    static void *start_consume(void *arg);
};
#endif