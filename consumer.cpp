#include "consumer.h"

Consumer::Consumer(Monitor *mon, Log_Helper *log_helper, int consumption_time, Consumers type)
{
    this->mon = mon;
    this->log_helper = log_helper;
    this->consumption_time = consumption_time;
    this->type = type;
    consumed = new unsigned int[2]{0, 0};
    mon->init_consumption_info_of_thread(type, consumed);
}

void Consumer::consume()
{
    while (!this->mon->consumed_all_requests())
    {
        RequestType returned_type = mon->consume_item();
        ++consumed[returned_type];
        log_helper->request_removed(this->type, returned_type, consumed);
        // std::this_thread::sleep_for(std::chrono::milliseconds(consumption_time));
        usleep(consumption_time * 1000);
    }
}

void *Consumer::start_consume(void *arg)
{
    Consumer *c = (Consumer *)arg;
    c->consume();
    return NULL;
}