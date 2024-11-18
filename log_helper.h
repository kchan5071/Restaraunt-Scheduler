/*
  Halie Do 827707836
  Kai Chan 827673009
 */
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

/**
 * @brief   Helper class to log the requests added and removed from the request queue
 *          and to print the history of the requests produced and consumed.
 */
class Log_Helper
{
private:
    std::vector<unsigned int> produced;
    std::vector<std::vector<unsigned int>> consumed;
    std::vector<unsigned int> inRequestQueue;

public:
    /**
     * @brief Construct a new Log_Helper object
     */
    Log_Helper();

    /**
     * @brief   Show that a request has been added to the request queue and
     *          print the current status of the request queue.
     *
     * @param type  What kind of request was produced?
     */
    void request_added(RequestType request_type);

    /**
     * @brief   Show that an item has been removed from the request queue
     *          and print the current status of the request queue.
     *
     * @param consumer  Who removed and processed the request?
     * @param type      What kind of request was removed?
     */
    void request_removed(Consumers consumer, RequestType request_type);

    /**
     * @brief   implements the output_production_history function from log.h
     */
    void history();
};
#endif