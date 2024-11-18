#include "consumer.h"


Consumer::Consumer(Monitor *mon, int consumption_time, Consumers type)
{
    this->mon = mon;
    this->consumption_time = consumption_time;
    this->type = type;
}


void Consumer::consume()
{
    // Consume items from the monitor
    while (!mon->buffer_empty() || !mon->finished_producing())
    {
        // Sleep for the consumption time
        usleep(consumption_time * microseconds_to_milliseconds);

        // Consume the item
        RequestType returned_type = mon->consume_item(this->type);

        // If the returned type is N, then break
        if (returned_type == RequestTypeN)
        {
            break;
        }
    }
}

void *Consumer::start_consume(void *arg)
{   
    // Start the consume function
    Consumer *c = (Consumer *)arg;
    c->consume();
    return NULL;
}