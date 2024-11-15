#include "log_helper.h"

Log_Helper::Log_Helper(Monitor *monitor) {
    produced = std::vector<unsigned int>(2, 0);
    consumed = std::vector<std::vector<unsigned int>>(2, std::vector<unsigned int>(2, 0));
    inRequestQueue = std::vector<unsigned int>(2, 0);
    this->monitor = monitor;
}

void Log_Helper::request_added(RequestType request_type, int producer) {
    produced[producer]++;
    inRequestQueue[request_type]++;
    output_request_added(request_type, produced.data(), inRequestQueue.data());
}

void Log_Helper::request_removed(Consumers consumer, RequestType request_type) {
    consumed[consumer][request_type]++;
    inRequestQueue[request_type]--;
    output_request_removed(consumer, request_type, consumed[consumer].data(), inRequestQueue.data());
}

void Log_Helper::history() {
    unsigned int** consumed = (unsigned int**)calloc(2, sizeof(unsigned int*));
    consumed[0] = this->consumed[0].data();
    consumed[1] = this->consumed[1].data();
    output_production_history(produced.data(), consumed);
}

std::vector<unsigned int> Log_Helper::convert_queue_to_vector(std::queue<Seating_Request> queue) {
    std::vector<unsigned int> vec;
    while (!queue.empty()) {
        vec.push_back(queue.front().type);
        queue.pop();
    }
    return vec;
}