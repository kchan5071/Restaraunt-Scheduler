#ifndef MONITOR_H
#define MONITOR_H

#include <queue>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include "seating.h"
#include "log_helper.h"

// defining requirements
#define MAX_SEATING_REQUESTS 18
#define MAX_VIP_REQUESTS 5

// defining conversion factor for microseconds to milliseconds
#define microseconds_to_milliseconds 1000

/**
 * @brief   Struct to hold the request type
 */
typedef struct Seating_Request
{
    RequestType type;
} Seating_Request;


/** 
 *  @brief  Monitor class to manage the buffer and the production and consumption of items
 *         from the buffer.
 */
class Monitor
{
private:
    // buffer to hold the requests
    std::queue<Seating_Request> buffer;

    // mutex and condition variables to manage the buffer
    pthread_mutex_t mutex;
    pthread_cond_t available_slots;
    pthread_cond_t unconsumed;
    pthread_cond_t VIP_available;


    // variables to track the number of productions and consumptions
    int max_productions;
    int produced;
    int consumed;
    int current_VIP;
    int waiting_producers;

    // logger to log the requests added and removed from the buffer
    Log_Helper* logger;

public:

    /** 
     * @brief Construct a new Monitor object (default constructor)
     */
    Monitor();

    /**
     * @brief Construct a new Monitor object
     * 
     * @param max_productions   The maximum number of productions
     * @param logger            The logger to log the requests added and removed from the buffer
     */
    Monitor(int max_productions, Log_Helper* logger);

    /**
     * @brief Destroy the Monitor object
     */
    ~Monitor();

    /**
     * @brief Produce an item of the given type
     * 
     * @param type  The type of the item to produce
     * @return true if the item was produced, false otherwise
     */
    bool produce_item(RequestType type);

    /**
     * @brief Consume an item of the given type
     * 
     * @param consumer  The consumer that is consuming the item
     * @return RequestType The type of the item consumed
     */
    RequestType consume_item(ConsumerType consumer);

    /**
     * @brief Check if the monitor is finished producing
     * 
     * @return true if the monitor is finished producing, false otherwise
     */
    void produce(RequestType type);

    /**
     * @brief Consume an item from the buffer
     * 
     * @return RequestType The type of the item consumed
     */
    RequestType consume();

    /**
     * @brief Check if the monitor is finished producing
     * 
     * @return true if the monitor is finished producing, false otherwise
     */
    bool finished_producing();

    /**
     * @brief Check if the monitor is finished consuming
     * 
     * @return true if the monitor is finished consuming, false otherwise
     */
    bool finished_consuming();

    /**
     * @brief Check if the buffer is empty
     * 
     * @return true if the buffer is empty, false otherwise
     */
    bool buffer_empty();

    /**
     * @brief Check if the buffer is full
     * 
     * @return true if the buffer is full, false otherwise
     */
    bool is_full();

    /**
     * @brief Get the number of items produced
     * 
     * @return int The number of items produced
     */
    int get_produced();

    /**
     * @brief Get the current number of VIP requests
     * 
     * @return int The current number of VIP requests
     */
    int get_current_VIP();

    /**
     * @brief Get the buffer
     * 
     * @return std::queue<Seating_Request> The buffer
     */
    std::queue<Seating_Request> get_buffer();
};

#endif