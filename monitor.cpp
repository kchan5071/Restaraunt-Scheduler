#include "monitor.h"

Monitor::Monitor(int max_productions, Log_Helper* logger)
{
    // initialize the mutex and condition variables
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
    // destroy the mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&available_slots);
    pthread_cond_destroy(&unconsumed);
    pthread_cond_destroy(&VIP_available);
}

bool Monitor::produce_item(RequestType type)
{
    // initialize the produced_item variable, this is used to determine if an item was produced
    // and returned to the producer
    bool produced_item = false;
    // lock the mutex
    pthread_mutex_lock(&mutex);
    // If the VIP room is full, wait for a signal from the consumer
    if (type == VIPRoom  && current_VIP >= MAX_VIP_REQUESTS)
    {
        waiting_producers++;
        pthread_cond_wait(&VIP_available, &mutex);
        waiting_producers--;
    }

    // If the buffer is full, wait for a signal from the consumer
    while (is_full())
    {
        waiting_producers++;
        pthread_cond_wait(&available_slots, &mutex);
        waiting_producers--;
    }

    // CRITICAL REGION----------------------------------------------

    // If the producer is not finished producing, produce an item
    if (!finished_producing())
    {
        // If the item is a VIP room request, increment the current VIP counter
        if (type == VIPRoom)
        {            
            current_VIP++;
        }
        // Produce the item and log the request
        produce(type);
        logger->request_added(type);
        produced_item = true;
    }

    // END CRITICAL REGION------------------------------------------

    // signal the consumer that there is an item to consume
    pthread_cond_signal(&unconsumed);
    // signal the producer that there is an available slot
    pthread_cond_signal(&available_slots);
    // unlock the mutex
    pthread_mutex_unlock(&mutex);
    return produced_item;
}

RequestType Monitor::consume_item(ConsumerType consumer)
{
    // lock the mutex
    pthread_mutex_lock(&mutex);

    // If the buffer is empty, wait for a signal from the producer
    while (buffer_empty())
    {
        // If the producer is finished producing, return N (which is used to break the loop in the consumer)
        if (finished_producing())
        {
            pthread_mutex_unlock(&mutex);
            return RequestTypeN;
        }
        pthread_cond_wait(&unconsumed, &mutex);
    }
    // CRITICAL REGION----------------------------------------------

    // Consume the item and log the request
    RequestType type = consume();
    logger->request_removed(consumer, type);

    // END CRITICAL REGION------------------------------------------
    
    pthread_cond_signal(&available_slots);
    // If the producer is finished producing, signal the consumer
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
    // Consume the item from the buffer
    Seating_Request request = buffer.front();
    buffer.pop();
    // If the item is a VIP room request, decrement the current VIP counter
    if (request.type == VIPRoom)
    {
        current_VIP--;
    }
    // If the current VIP counter is less than the max VIP requests, signal the producer
    if (current_VIP < MAX_VIP_REQUESTS)
    {
        pthread_cond_signal(&VIP_available);
    }
    consumed++;
    return request.type;
}

bool Monitor::finished_producing()
{
    // If the number of produced items is greater than or equal to the max productions minus the number of waiting producers
    return produced >= max_productions - waiting_producers;
}
bool Monitor::finished_consuming()
{ 
    // If the number of consumed items is greater than or equal to the max productions
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
