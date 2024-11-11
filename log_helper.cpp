#include "log_helper.h"

Log_Helper::Log_Helper(Monitor *monitor) {
    produced = std::vector<unsigned int>(2, 0);
    consumed = std::vector<unsigned int>(2, 0);
    inRequestQueue = std::vector<unsigned int>(2, 0);
    this->monitor = monitor;
}

void Log_Helper::request_added(RequestType request_type) {
    produced.push_back(request_type);
    inRequestQueue.push_back(request_type);
    output_request_added(request_type, produced.data(), inRequestQueue.data());
}

void Log_Helper::request_removed(Consumers consumer, RequestType request_type) {
    consumed.push_back(request_type);
    inRequestQueue.erase(std::remove(inRequestQueue.begin(), inRequestQueue.end(), request_type), inRequestQueue.end());
    output_request_removed(consumer, request_type, produced.data(), inRequestQueue.data());
}

void Log_Helper::history() {
    // output_production_history(produced.data(), consumed.data());
}

std::vector<unsigned int> Log_Helper::convert_queue_to_vector(std::queue<Seating_Request> queue) {
    std::vector<unsigned int> vec;
    while (!queue.empty()) {
        vec.push_back(queue.front().type);
        queue.pop();
    }
    return vec;
}