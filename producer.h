#ifndef PRODUCER_H
#define PRODUCER_H

#include <thread>
#include <chrono>
#include "monitor.h"
#include "seating.h"
/**
 * @brief   Producer class to produce items of a given type
 */
class Producer
{
private:
    Monitor *mon;
    RequestType type;
    int production_time;

public:
    /**
     * @brief Construct a new Producer object
     * 
     * @param mon               The monitor to produce items to
     * @param production_time   The time to produce an item
     * @param type              The type of item to produce
     */
    Producer(Monitor *mon, int production_time, RequestType type);

    /**
     * @brief Produce items of the given type
     */
    void produce();

    /**
     * @brief Start the produce function
     * 
     * @param arg   The producer object
     * @return void* 
     */
    static void *start_produce(void *arg);
};
#endif