#include "producer.h"

#define MILLISECONDS_TO_MICROSECONDS 1000

Producer::Producer(Monitor *mon, int production_time, RequestType type)
{
    this->mon = mon;
    this->production_time = production_time;
    this->type = type;
}

void Producer::produce()
{
    while (!this->mon->finished_producing_requests()) // TODO: add lock? --> accessing shared data
    {
        this->mon->produce_item(this->type);
        bool flag = this->mon->finished_producing_requests();
        // log_helper->request_added(this->type);
        usleep(production_time * MILLISECONDS_TO_MICROSECONDS); // multiply production time by 1000 to convert milliseconds to microseconds to pass into usleep
    }
}

void *Producer::start_produce(void *arg)
{
    Producer *p = (Producer *)arg;
    p->produce();
    return NULL;
}