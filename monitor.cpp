#include "monitor.h"

Monitor::Monitor(int max_productions, Log_Helper* logger)
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&available_slots, NULL);
    pthread_cond_init(&unconsumed, NULL);
    pthread_cond_init(&VIP_available, NULL);
    this->max_productions = max_productions;
    current_VIP = 0;
    produced = 0;
    consumed = 0;
    waiting_producers = 0;
    this->logger = logger;
}

Monitor::~Monitor()
{
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&available_slots);
    pthread_cond_destroy(&unconsumed);
}

bool Monitor::produce_item(RequestType type)
{
    bool produced_item = false;
    pthread_mutex_lock(&mutex);
    if (type == VIPRoom  && current_VIP >= MAX_VIP_REQUESTS)
    {
        waiting_producers++;
        pthread_cond_wait(&VIP_available, &mutex);
        waiting_producers--;
    }
    while (is_full())
    {
        waiting_producers++;
        pthread_cond_wait(&available_slots, &mutex);
        waiting_producers--;
    }

    if (!finished_producing())
    {
        if (type == VIPRoom)
        {            
            current_VIP++;
        }
        produce(type);
        logger->request_added(type);
        produced_item = true;
    }
    pthread_cond_signal(&unconsumed);
    pthread_cond_signal(&available_slots);
    pthread_mutex_unlock(&mutex);
    return produced_item;
}

RequestType Monitor::consume_item(ConsumerType consumer)
{
    pthread_mutex_lock(&mutex);
    while (buffer_empty())
    {
        if (finished_producing())
        {
            pthread_mutex_unlock(&mutex);
            return RequestTypeN;
        }
        pthread_cond_wait(&unconsumed, &mutex);
    }

    RequestType type = consume();
    logger->request_removed(consumer, type);
    pthread_cond_signal(&available_slots);
    if (finished_producing())
    {
        pthread_cond_signal(&unconsumed);
    }
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
    if (request.type == VIPRoom)
    {
        current_VIP--;
    }
    if (current_VIP < MAX_VIP_REQUESTS)
    {
        pthread_cond_signal(&VIP_available);
    }
    consumed++;
    return request.type;
}

bool Monitor::finished_producing()
{
    return produced >= max_productions - waiting_producers;
}
bool Monitor::finished_consuming()
{
    return consumed >= max_productions;
}

int Monitor::get_produced()
{
    return produced;
}

int Monitor::get_current_VIP()
{
    return current_VIP;
}

bool Monitor::buffer_empty()
{
    return buffer.empty();
}

bool Monitor::is_full()
{
    return buffer.size() >= MAX_SEATING_REQUESTS;
}

std::queue<Seating_Request> Monitor::get_buffer()
{
    return buffer;
}
