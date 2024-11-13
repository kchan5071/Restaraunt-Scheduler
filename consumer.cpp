#include "consumer.h"

Consumer::Consumer(Monitor *mon, Log_Helper *log_helper, int consumption_time, Consumers type)
{
    this->mon = mon;
    this->log_helper = log_helper;
    this->consumption_time = consumption_time;
    this->type = type;
    mon->init_consumption_info_of_thread(type);
}

void Consumer::consume()
{
    while (!this->mon->consumed_all_requests()) // TODO: add lock --> accessing shared data
    {
        RequestType returned_type = mon->consume_item(type);
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