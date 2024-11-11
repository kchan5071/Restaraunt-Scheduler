#include "producer.h"

Producer::Producer(Monitor* mon, int production_time, RequestType type) {
    this->mon = mon;
    this->production_time = production_time;
    this->type = type;
}

void Producer::produce() {
    while (!this->mon->is_finished()) {
        this->mon->produce_item(this->type);
        sleep(production_time);
    }
}

void* Producer::start_produce(void* arg) {
    Producer* p = (Producer*) arg;
    p->produce();
    return NULL;
}