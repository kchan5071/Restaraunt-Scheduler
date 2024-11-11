#ifndef MONITOR_H
#define MONITOR_H

#include <queue>
#include <pthread.h>
#include <string>
#include <unistd.h>

#define DEFAULT_MAX_PRODUCTIONS 120
#define MAX_SEATING_REQUESTS 18
#define MAX_VIP_REQUESTS 5

typedef struct Seating_Request {
    std::string type;
} Seating_Request;

class Monitor {
private:
    std::queue<Seating_Request> buffer;
    pthread_mutex_t mutex;
    pthread_cond_t cond;

    int max_productions;
    int produced;
    int current_VIP;

public:
    Monitor();

    Monitor(int max_productions);

    ~Monitor();

    void produce_item(std::string type);

    void consume_item();

    void produce(std::string type);

    void consume();

    bool is_finished();

    bool is_full();
};

#endif