#include "consumer.h"

Consumer::Consumer(Monitor *mon, int consumption_time, Consumers type)
{
    this->mon = mon;
    this->consumption_time = consumption_time;
    this->type = type;
    mon->init_consumption_info_of_thread(type);
}

void Consumer::consume()
{
    while (!this->mon->consumed_all_requests()) // TODO: add lock --> accessing shared data
    {
        this->mon->consume_item(type);
        // log_helper->request_removed(this->type, returned_type, consumed);
        usleep(consumption_time * 1000); // usleep takes microseconds, multiple consumption_time by 1000 to get # of milliseconds in microseconds
    }
}

void *Consumer::start_consume(void *arg)
{
    Consumer *c = (Consumer *)arg;
    c->consume();
    return NULL;
}