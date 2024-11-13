#ifndef MONITOR_H
#define MONITOR_H

#include <queue>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include "seating.h"
extern "C"
{
#include "log.h"
}
#define DEFAULT_MAX_PRODUCTIONS 120
#define MAX_SEATING_REQUESTS 18
#define MAX_VIP_REQUESTS 5

typedef struct Seating_Request
{
    RequestType type;
} Seating_Request;

class Monitor
{
private:
    std::queue<Seating_Request> buffer;
    pthread_mutex_t mutex;
    pthread_mutex_t mutex_p_bool;
    pthread_mutex_t mutex_c_bool;
    pthread_cond_t cond;

    int max_productions;
    int total_produced;
    int total_consumed;
    unsigned int *produced;
    unsigned int **consumed;
    unsigned int *in_request_queue;
    int current_VIP;

public:
    Monitor();

    Monitor(int max_productions);

    ~Monitor();

    void produce_item(RequestType type);

    RequestType consume_item(Consumers consumer);

    void produce(RequestType type);

    RequestType consume();
    void init_consumption_info_of_thread(ConsumerType type);
    unsigned int **get_consumption_info_of_all_threads();

    bool finished_producing_requests();
    bool consumed_all_requests();

    bool is_full();
    unsigned int *get_produced_arr();

    int get_total_consumed();
    int get_total_produced();

    std::queue<Seating_Request> get_buffer();
};

#endif