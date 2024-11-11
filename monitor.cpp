#include "monitor.h"

Monitor::Monitor() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    max_productions = DEFAULT_MAX_PRODUCTIONS;
    produced = 0;
    current_VIP = 0;
}

Monitor::Monitor(int max_productions) {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    this->max_productions = max_productions;
}

Monitor::~Monitor() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

void Monitor::produce_item(std::string type) {
    pthread_mutex_lock(&mutex);
    while (is_full() || (type == "VIP" && current_VIP >= MAX_VIP_REQUESTS)) {
        pthread_cond_wait(&cond, &mutex);
    }
    if (type == "VIP") {
        current_VIP++;
    }
    produce(type);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

void Monitor::consume_item() {
    pthread_mutex_lock(&mutex);
    while (buffer.empty()) {
        pthread_cond_wait(&cond, &mutex);
    }
    consume();
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

void Monitor::produce(std::string type) {
    Seating_Request request;
    request.type = type;
    buffer.push(request);
    produced++;
    printf("Produced %s\n", type.c_str());
}

void Monitor::consume() {
    Seating_Request request = buffer.front();
    buffer.pop();
    printf("Consumed %s\n", request.type.c_str());
    if (request.type == "VIP") {
        current_VIP--;
    }
}

bool Monitor::is_finished() {
    return produced >= max_productions;
}

bool Monitor::is_full() {
    return buffer.size() >= MAX_SEATING_REQUESTS;
}
