#include "monitor.h"

Monitor::Monitor(int max_productions) {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    this->max_productions = max_productions;
    current_VIP = 0;
    produced = 0;
    waiting_producers = 0;

}

Monitor::~Monitor()
{
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex_c_bool);
    pthread_mutex_destroy(&mutex_p_bool);
    pthread_cond_destroy(&cond);
}

void Monitor::produce_item(RequestType type)
{
    pthread_mutex_lock(&mutex);
    while (is_full() || (type == VIPRoom && current_VIP >= MAX_VIP_REQUESTS)) {
        waiting_producers++;
        pthread_cond_wait(&cond, &mutex);
        waiting_producers--;
    }
    if (type == VIPRoom)
    {
        current_VIP++;
    }
    produce(type);
    output_request_added(type, produced, in_request_queue);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

RequestType Monitor::consume_item(Consumers consumer)
{
    pthread_mutex_lock(&mutex);
    while (buffer_empty()) {
        pthread_cond_wait(&cond, &mutex);
        if (buffer_empty() && is_finished()) {
            pthread_mutex_unlock(&mutex);
            return RequestTypeN;
        }
    }
    RequestType type = consume();
    consumed[consumer][type]++;
    output_request_removed(consumer, type, consumed[type], in_request_queue);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return type;
}

void Monitor::produce(RequestType type)
{
    Seating_Request request;
    request.type = type;
    buffer.push(request);
    produced++;

}

RequestType Monitor::consume()
{
    Seating_Request request = buffer.front();
    buffer.pop();
    if (request.type == VIPRoom) {
        current_VIP--;
    }
    total_consumed++;
    return request.type;
}

bool Monitor::is_finished() {
    return produced >= max_productions - waiting_producers;
}

int Monitor::get_produced() {
    return produced;
}

int Monitor::get_current_VIP() {
    return current_VIP;
}

bool Monitor::buffer_empty() {
    return buffer.empty();
}

bool Monitor::consumed_all_requests()
{
    // pthread_mutex_lock(&mutex_c_bool);
    bool finished = total_consumed == max_productions;
    // pthread_mutex_unlock(&mutex_c_bool);
    return finished;
}

int Monitor::get_total_consumed()
{
    return total_consumed;
}

int Monitor::get_total_produced()
{
    return total_produced;
}

bool Monitor::is_full()
{
    return buffer.size() == MAX_SEATING_REQUESTS;
}

std::queue<Seating_Request> Monitor::get_buffer()
{
    return buffer;
}

unsigned int *Monitor::get_produced_arr()
{
    return produced;
}

unsigned int **Monitor::get_consumption_info_of_all_threads()
{
    return consumed;
}