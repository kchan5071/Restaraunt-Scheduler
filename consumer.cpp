#include "consumer.h"

Consumer::Consumer(Monitor *mon, Log_Helper *log_helper, int consumption_time, Consumers type)
{
    this->mon = mon;
    this->consumption_time = consumption_time;
    this->type = type;
    this->log_helper = log_helper;
}

void Consumer::consume()
{
    while (!mon->buffer_empty() || !mon->finished_producing())
    {
        usleep(consumption_time * microseconds_to_milliseconds);
        RequestType returned_type = mon->consume_item();
        if (returned_type == RequestTypeN)
        {
            break;
        }
        log_helper->request_removed(this->type, returned_type);
    }
}

void *Consumer::start_consume(void *arg)
{
    Consumer *c = (Consumer *)arg;
    c->consume();
    return NULL;
}