#include "VIP_Producer.h"

VIP_Producer::VIP_Producer(Monitor* mon, int production_time) : Producer(mon, production_time, "VIP") {
    this->type = "VIP";
}

void VIP_Producer::produce() {
    while (!this->mon->is_finished()) {
        this->mon->produce_item(this->type);
        sleep(production_time);
    }
}