#ifndef MONITOR_H
#define MONITOR_H

#include <queue>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include "seating.h"

#define MAX_SEATING_REQUESTS 18
#define MAX_VIP_REQUESTS 5
#define microseconds_to_milliseconds 1000

typedef struct Seating_Request {
    RequestType type;
} Seating_Request;

class Monitor {
private:
    std::queue<Seating_Request> buffer;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

    int max_productions;
    int produced;
    int current_VIP;
    int waiting_producers;

public:
    Monitor();

    Monitor(int max_productions);

    ~Monitor();

    void produce_item(RequestType type);

    RequestType consume_item();

    void produce(RequestType type);

    RequestType consume();

    bool is_finished();

    bool buffer_empty();

    bool is_full();

    int get_produced();

    int get_current_VIP();

    std::queue<Seating_Request> get_buffer();
};

#endif