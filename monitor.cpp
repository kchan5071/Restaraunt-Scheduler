#include "monitor.h"

Monitor::Monitor(int max_productions)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    this->max_productions = max_productions;
    total_produced = 0;
    total_consumed = 0;
    consumed = new unsigned int *[2];
    produced = new unsigned int[2]{0, 0};
    in_request_queue = new unsigned int[2]{0, 0};
    current_VIP = 0;
}

Monitor::~Monitor()
{
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

void Monitor::produce_item(RequestType type)
{
    pthread_mutex_lock(&mutex);
    while (is_full() || (type == VIPRoom && current_VIP >= MAX_VIP_REQUESTS))
    {
        pthread_cond_wait(&cond, &mutex);
    }
    if (type == VIPRoom)
    {
        current_VIP++;
    }
    produce(type);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

RequestType Monitor::consume_item()
{
    pthread_mutex_lock(&mutex);
    while (buffer.empty())
    {
        pthread_cond_wait(&cond, &mutex);
    }
    RequestType type = consume();
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return type;
}

void Monitor::produce(RequestType type)
{
    Seating_Request request;
    request.type = type;
    buffer.push(request);
    in_request_queue[type]++;
    // printf("Produced %s\n", producerAbbrevs[type]);
    total_produced++;
    produced[type]++;
}

RequestType Monitor::consume()
{
    Seating_Request request = buffer.front();
    buffer.pop();
    in_request_queue[request.type]--;
    // printf("Consumed %s\n", producerAbbrevs[request.type]);
    if (request.type == VIPRoom)
    {
        current_VIP--;
    }
    total_consumed++;
    return request.type;
}

void Monitor::init_consumption_info_of_thread(ConsumerType type, unsigned int arr[])
{
    consumed[type] = arr;
}

bool Monitor::finished_producing_requests()
{
    return total_produced == max_productions;
}

bool Monitor::consumed_all_requests()
{
    return total_consumed == max_productions;
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

unsigned int *Monitor::get_request_queue()
{
    return in_request_queue;
}

unsigned int **Monitor::get_consumption_info_of_all_threads()
{
    return consumed;
}