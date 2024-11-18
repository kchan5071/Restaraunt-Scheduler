#include "consumer.h"

Consumer::Consumer(Monitor *mon, int consumption_time, Consumers type)
{
    this->mon = mon;
    this->consumption_time = consumption_time;
    this->type = type;
}

void Consumer::consume()
{
    while (!mon->buffer_empty() || !mon->finished_producing())
    {
        usleep(consumption_time * microseconds_to_milliseconds);
        RequestType returned_type = mon->consume_item(this->type);
        if (returned_type == RequestTypeN)
        {
            break;
        }
    }
}

void *Consumer::start_consume(void *arg)
{
    Consumer *c = (Consumer *)arg;
    c->consume();
    return NULL;
}