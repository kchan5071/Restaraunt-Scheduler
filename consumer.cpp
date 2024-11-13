#include "consumer.h"

Consumer::Consumer(Monitor *mon, Log_Helper *log_helper, int consumption_time, Consumers type)
{
    this->mon = mon;
    this->log_helper = log_helper;
    this->consumption_time = consumption_time;
    this->type = type;
    mon->init_consumption_info_of_thread(type);
}

void Consumer::consume() {
    while (!mon->buffer_empty() || !mon->is_finished()) {
        RequestType returned_type = mon->consume_item();
        if (returned_type == RequestTypeN) {
            break;
        }
        log_helper->request_removed(this->type, returned_type);
        usleep(consumption_time * microseconds_to_milliseconds);

    }
}

void *Consumer::start_consume(void *arg)
{
    Consumer *c = (Consumer *)arg;
    c->consume();
    return NULL;
}