#ifndef LOG_HELPER_H
#define LOG_HELPER_H

#include <queue>
#include <vector>
#include <cstdlib>
#include "seating.h"

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

public:
    Log_Helper();
    ~Log_Helper();
    void request_added(RequestType request_type);
    void request_removed(Consumers consumer, RequestType request_type);
    void history();
};
#endif