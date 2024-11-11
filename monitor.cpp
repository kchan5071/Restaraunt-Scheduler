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

void Monitor::produce_item(RequestType type) {
    pthread_mutex_lock(&mutex);
    while (is_full() || (type == VIPRoom && current_VIP >= MAX_VIP_REQUESTS)) {
        pthread_cond_wait(&cond, &mutex);
    }
    if (type == VIPRoom) {
        current_VIP++;
    }
    produce(type);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

RequestType Monitor::consume_item() {
    pthread_mutex_lock(&mutex);
    while (buffer.empty()) {
        pthread_cond_wait(&cond, &mutex);
    }
    RequestType type = consume();
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return type;
}

void Monitor::produce(RequestType type) {
    Seating_Request request;
    request.type = type;
    buffer.push(request);
    printf("Produced %s\n", producerAbbrevs[type]);
    produced++;
}

RequestType Monitor::consume() {
    Seating_Request request = buffer.front();
    buffer.pop();
    printf("Consumed %s\n", producerAbbrevs[request.type]);
    if (request.type == VIPRoom) {
        current_VIP--;
    }
    return request.type;
}

bool Monitor::is_finished() {
    return produced >= max_productions;
}

bool Monitor::is_full() {
    return buffer.size() >= MAX_SEATING_REQUESTS;
}

std::queue<Seating_Request> Monitor::get_buffer() {
    return buffer;
}
