
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <getopt.h>


#include "monitor.h"
#include "log.h"
#include "seating.h"
#include "producer.h"
#include "consumer.h"
#include "log_helper.h"


#define DEFAULT_MAX_PRODUCTIONS 120
#define DEFAULT_PRODUCTION_TIME 0
#define DEFAULT_CONSUMPTION_TIME 0

#define MAX_PRODUCTION_ARG = "-s"
#define T_X_ARG = "-x"
#define REV9_ARG = "-r"
#define GENERAL_TABLE_ARG = "-g"
#define VIP_ROOM_ARG = "-v"

typedef struct Thread_Args {
    Monitor* mon;
    int max_productions;
    int rev_9_consumption_time;
    int t_x_consumption_time;
    int general_table_production_time;
    int vip_room_production_time;
} Thread_Args;

Thread_Args parse_args(int argc, char* argv[]) {
    Thread_Args args;
    args.max_productions = DEFAULT_MAX_PRODUCTIONS;
    args.rev_9_consumption_time = DEFAULT_CONSUMPTION_TIME;
    args.t_x_consumption_time = DEFAULT_CONSUMPTION_TIME;
    args.general_table_production_time = DEFAULT_PRODUCTION_TIME;
    args.vip_room_production_time = DEFAULT_PRODUCTION_TIME;

    int opt;
    while ((opt = getopt(argc, argv, "s:x:r:g:v:")) != -1) {
        switch (opt) {
            case 's':
                args.max_productions = atoi(optarg);
                break;
            case 'x':
                args.rev_9_consumption_time = atoi(optarg);
                break;
            case 'r':
                args.t_x_consumption_time = atoi(optarg);
                break;
            case 'g':
                args.general_table_production_time = atoi(optarg);
                break;
            case 'v':
                args.vip_room_production_time = atoi(optarg);
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " [-s max_productions] [-x rev_9_consumption_time] [-r t_x_consumption_time] [-g general_table_production_time] [-v vip_room_production_time]" << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    return args;
}

int main(int argc, char* argv[]) {
    Thread_Args args = parse_args(argc, argv);

    Monitor mon = Monitor(args.max_productions);
    Log_Helper log_helper(&mon);

    pthread_t general_producer_thread;
    pthread_t vip_producer_thread;
    pthread_t t_x_consumer_thread;
    pthread_t rev_9_consumer_thread;

    Producer general_producer(&mon, &log_helper, args.general_table_production_time, GeneralTable);
    Producer vip_producer(&mon, &log_helper, args.vip_room_production_time, VIPRoom);
    Consumer t_x_consumer(&mon, &log_helper, args.t_x_consumption_time, TX);
    Consumer rev_9_consumer(&mon, &log_helper, args.rev_9_consumption_time, Rev9);

    pthread_create(&general_producer_thread, NULL, Producer::start_produce, &general_producer);
    pthread_create(&vip_producer_thread, NULL, Producer::start_produce, &vip_producer);
    pthread_create(&t_x_consumer_thread, NULL, Consumer::start_consume, &t_x_consumer);
    pthread_create(&rev_9_consumer_thread, NULL, Consumer::start_consume, &rev_9_consumer);

    pthread_join(general_producer_thread, NULL);
    pthread_join(vip_producer_thread, NULL);
    pthread_join(t_x_consumer_thread, NULL);
    pthread_join(rev_9_consumer_thread, NULL);

    log_helper.history();
    return 0;
}
