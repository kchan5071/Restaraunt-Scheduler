#include "general_producer.h"

General_Producer::General_Producer(Monitor* mon, int production_time) : Producer(mon, production_time, "General_Table") {
    this->type = "General_Table";
}

void General_Producer::produce() {
    while (!this->mon->is_finished()) {
        this->mon->produce_item(this->type);
        sleep(production_time);
    }
}