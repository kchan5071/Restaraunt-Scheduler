#include "producer.h"

Producer::Producer(Monitor *mon, Log_Helper *log_helper, int production_time, RequestType type)
{
    this->mon = mon;
    this->log_helper = log_helper;
    this->production_time = production_time;
    this->type = type;
}

void Producer::produce()
{
    while (!this->mon->finished_producing_requests()) // TODO: add lock? --> accessing shared data
    {
        this->mon->produce_item(this->type);
        log_helper->request_added(this->type, this->type);
        usleep(production_time * microseconds_to_milliseconds);
    } 
}

void *Producer::start_produce(void *arg)
{
    Producer *p = (Producer *)arg;
    p->produce();
    return NULL;
}