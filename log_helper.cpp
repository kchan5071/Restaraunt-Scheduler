#include "log_helper.h"

Log_Helper::Log_Helper(Monitor *monitor)
{
    pthread_mutex_init(&mutex, NULL);

    // produced = new unsigned int[2]{0, 0};
    // // consumed = std::vector<unsigned int>(2, 0);
    // inRequestQueue = new unsigned int[2]{0, 0};
    this->monitor = monitor;
}

void Log_Helper::request_added(RequestType request_type)
{
    pthread_mutex_lock(&mutex);
    // produced.push_back(request_type);
    // inRequestQueue.push_back(request_type);
    // ++produced[request_type];
    // ++inRequestQueue[request_type];
    output_request_added(request_type, monitor->get_produced_arr(), monitor->get_request_queue());
    // printf("Total requests produced: %d\n", monitor->get_total_produced());
    pthread_mutex_unlock(&mutex);
}

void Log_Helper::request_removed(Consumers consumer, RequestType request_type, unsigned int *consumed)
{
    pthread_mutex_lock(&mutex);
    // consumed.push_back(request_type);
    // --inRequestQueue[request_type];
    // inRequestQueue.erase(std::remove(inRequestQueue.begin(), inRequestQueue.end(), request_type), inRequestQueue.end());
    output_request_removed(consumer, request_type, consumed, monitor->get_request_queue());
    pthread_mutex_unlock(&mutex);
}

void Log_Helper::history()
{
    output_production_history(monitor->get_produced_arr(), monitor->get_consumption_info_of_all_threads());
}

std::vector<unsigned int> Log_Helper::convert_queue_to_vector(std::queue<Seating_Request> queue)
{
    std::vector<unsigned int> vec;
    while (!queue.empty())
    {
        vec.push_back(queue.front().type);
        queue.pop();
    }
    return vec;
}