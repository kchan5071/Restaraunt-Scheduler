#ifndef MONITOR_H
#define MONITOR_H

#include <queue>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include "seating.h"
#include "log_helper.h"

#define MAX_SEATING_REQUESTS 18
#define MAX_VIP_REQUESTS 5
#define microseconds_to_milliseconds 1000

typedef struct Seating_Request
{
    RequestType type;
} Seating_Request;

class Monitor
{
private:
    std::queue<Seating_Request> buffer;
    pthread_mutex_t mutex;
    pthread_cond_t available_slots;
    pthread_cond_t unconsumed;
    pthread_cond_t VIP_available;

    int max_productions;
    int produced;
    int consumed;
    int current_VIP;
    int waiting_producers;
    Log_Helper* logger;

public:
    Monitor();

    Monitor(int max_productions, Log_Helper* logger);

    ~Monitor();

    bool produce_item(RequestType type);

    RequestType consume_item(ConsumerType consumer);

    void produce(RequestType type);

    RequestType consume();

    bool finished_producing();
    bool finished_consuming();

    bool buffer_empty();

    bool is_full();

    int get_produced();

    int get_current_VIP();

    std::queue<Seating_Request> get_buffer();
};

#endif