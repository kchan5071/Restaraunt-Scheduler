#include "consumer.h"

Consumer::Consumer(Monitor* mon, int consumption_time, Consumers type) {
    this->mon = mon;
    this->consumption_time = consumption_time;
    this->type = type;
}

void Consumer::consume() {
    while (!this->mon->is_finished()) {
        this->mon->consume_item();
        sleep(consumption_time);
    }
}

void* Consumer::start_consume(void* arg) {
    Consumer* c = (Consumer*) arg;
    c->consume();
    return NULL;
}