#include "log_helper.h"
/*
  Halie Do 827707836
  Kai Chan 827673009
 */

Log_Helper::Log_Helper()
{
    produced = std::vector<unsigned int>(NUMBER_OF_PRODUCERS, 0);
    consumed = std::vector<std::vector<unsigned int>>(2, std::vector<unsigned int>(NUMBER_OF_CONSUMERS, 0));
    inRequestQueue = std::vector<unsigned int>(NUMBER_OF_REQUEST_TYPES, 0);
}

void Log_Helper::request_added(RequestType request_type)
{
    // Increment the produced and inRequestQueue counters
    produced[request_type]++;
    inRequestQueue[request_type]++;

    // Output the request added
    output_request_added(request_type, produced.data(), inRequestQueue.data());
}

void Log_Helper::request_removed(Consumers consumer, RequestType request_type)
{
    // Increment the consumed and decrement the inRequestQueue counters
    this->consumed[consumer][request_type]++;
    this->inRequestQueue[request_type]--;

    // Output the request removed
    output_request_removed(consumer, request_type, consumed[consumer].data(), inRequestQueue.data());
}

void Log_Helper::history()
{
    // Output the production history
    unsigned int **consumed = (unsigned int **)calloc(NUMBER_OF_PRODUCERS, sizeof(unsigned int *));

    // split the consumed vector into two arrays
    consumed[0] = this->consumed[0].data();
    consumed[1] = this->consumed[1].data();

    // output the production history
    output_production_history(produced.data(), consumed);
}