#ifndef LOG_HELPER_H
#define LOG_HELPER_H

#include <queue>
#include <vector>
#include "seating.h"
#include "monitor.h"

extern "C"
{
#include "log.h"
}

class Log_Helper
{
private:
    std::vector<unsigned int> produced;
    std::vector<std::vector<unsigned int>> consumed;
    std::vector<unsigned int> inRequestQueue;
    Monitor *monitor;
    std::vector<unsigned int> convert_queue_to_vector(std::queue<Seating_Request> queue);
    pthread_mutex_t mutex;

public:
    Log_Helper(Monitor *monitor);
    ~Log_Helper();
    void request_added(RequestType request_type, int producer);
    void request_removed(Consumers consumer, RequestType request_type);
    void history();
};
#endif