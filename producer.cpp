#include "producer.h"

Producer::Producer(Monitor *mon, int production_time, RequestType type)
{
    this->mon = mon;
    this->production_time = production_time;
    this->type = type;
}

void Producer::produce()
{
    // Produce items until the monitor is finished producing
    while (!this->mon->finished_producing())
    {
        // Sleep for the production time
        usleep(production_time * microseconds_to_milliseconds);

        // Produce the item
        this->mon->produce_item(this->type);
    }
}

void *Producer::start_produce(void *arg)
{
    // Start the produce function
    Producer *p = (Producer *)arg;
    p->produce();
    return NULL;
}