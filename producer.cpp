#include "producer.h"

Producer::Producer(Monitor *mon, int production_time, RequestType type)
{
    this->mon = mon;
    this->production_time = production_time;
    this->type = type;
}

void Producer::produce()
{
    while (!this->mon->finished_producing())
    {
        usleep(production_time * microseconds_to_milliseconds);
        this->mon->produce_item(this->type);
    }
}

void *Producer::start_produce(void *arg)
{
    Producer *p = (Producer *)arg;
    p->produce();
    return NULL;
}