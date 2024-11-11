#include "consumer.h"

Consumer::Consumer(Monitor* mon, Log_Helper* log_helper, int consumption_time, Consumers type) {
    this->mon = mon;
    this->consumption_time = consumption_time;
    this->type = type;
    this->log_helper = log_helper;
}

void Consumer::consume() {
    while (!this->mon->is_finished()) {
        RequestType returned_type = mon->consume_item();
        log_helper->request_removed(this->type, returned_type);
        sleep(consumption_time);
    }
}

void* Consumer::start_consume(void* arg) {
    Consumer* c = (Consumer*) arg;
    c->consume();
    return NULL;
}