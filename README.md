# Multi-Threaded Producer-Consumer Simulation

## Overview

This project simulates a **multi-threaded producer-consumer system** using C++. It employs threads to run multiple producers and consumers concurrently, ensuring efficient interaction with shared resources. A monitor is used to synchronize thread operations and manage access to critical sections, preventing race conditions. The simulation also logs the production and consumption events for detailed insights.

## Features

- **Multi-Threading**: Utilizes multiple threads for concurrent producers and consumers, enhancing simulation realism and efficiency.
- **Producers**: Simulate the production of resources for general tables and VIP rooms.
- **Consumers**: Simulate the consumption of resources for Rev9 and TX queues.
- **Monitor**: Implements thread-safe synchronization to manage shared resources effectively.
- **Logging**: Tracks the entire simulation process, including detailed records of production and consumption events.

## Files

- **`main.cpp`**: The entry point of the program, initializes threads and starts the simulation.
- **`monitor.h` and `monitor.cpp`**: Implements the monitor for thread synchronization and safe resource sharing.
- **`log.h` and `log.cpp`**: Manages logging functionality to record events in the simulation.
- **`seating.h` and `seating.cpp`**: Defines resource types (e.g., GeneralTable, VIPRoom) for producers and consumers.
- **`producer.h` and `producer.cpp`**: Defines the logic for producer threads to generate resources.
- **`consumer.h` and `consumer.cpp`**: Defines the logic for consumer threads to consume resources.
- **`log_helper.h` and `log_helper.cpp`**: Assists with logging and printing the history of simulation events.

## Command-Line Arguments

The program accepts the following command-line arguments to configure the simulation:

| Argument | Description                            | Default Value |
| -------- | -------------------------------------- | ------------- |
| `-s`     | Maximum number of productions to allow | 120           |
| `-x`     | Consumption time for TX resource       | 0             |
| `-r`     | Consumption time for Rev9 resource     | 0             |
| `-g`     | Production time for GeneralTable       | 0             |
| `-v`     | Production time for VIPRoom            | 0             |

### Example Command:

```
./producer_consumer_simulation -s 100 -x 2 -r 3 -g 1 -v 1
```

This sets:

- Maximum productions: `100`
- TX consumption time: `2`
- Rev9 consumption time: `3`
- General table production time: `1`
- VIP room production time: `1`

## How to Build

    Ensure you have a C++ compiler (e.g., g++) installed.
    Compile the program with multi-threading support using the following command:

```
g++ -pthread -o producer_consumer_simulation main.cpp monitor.cpp log.cpp seating.cpp producer.cpp consumer.cpp log_helper.cpp
```

## How to Run

Run the program with the desired configuration:
`./dineseating [options]`

Replace [options] with your desired command-line arguments (e.g., `-s`, `-x`, etc.).

## How It Works

- Initialization: The monitor and log helper are created, and threads for producers and consumers are initialized.
- Thread Execution:
  - Producers: Produce resources (GeneralTable, VIPRoom) and store them in a shared space.
  - Consumers: Consume resources (Rev9, TX) from the shared space.
  - The threads operate concurrently, with the monitor managing synchronization to prevent race conditions.
- Logging: All production and consumption events are logged for analysis.
- Completion: After all threads finish their tasks, the program outputs the event history.

## Sample Output

```
Request queue: 0 GT + 1 VIP = 1. Added VIP room request. Produced: 0 GT + 1 VIP = 1 in 0.000 s.
Request queue: 0 GT + 0 VIP = 0. T-X consumed VIP room request.  T-X totals: 0 GT + 1 VIP = 1 consumed in 0.000 s.
Request queue: 1 GT + 0 VIP = 1. Added General table request. Produced: 1 GT + 1 VIP = 2 in 0.005 s.
Request queue: 0 GT + 0 VIP = 0. REV-9 consumed General table request.  REV-9 totals: 1 GT + 0 VIP = 1 consumed in 0.005 s.
Request queue: 0 GT + 1 VIP = 1. Added VIP room request. Produced: 1 GT + 2 VIP = 3 in 0.011 s.
Request queue: 1 GT + 1 VIP = 2. Added General table request. Produced: 2 GT + 2 VIP = 4 in 0.020 s.
Request queue: 1 GT + 2 VIP = 3. Added VIP room request. Produced: 2 GT + 3 VIP = 5 in 0.021 s.
Request queue: 1 GT + 1 VIP = 2. T-X consumed VIP room request.  T-X totals: 0 GT + 2 VIP = 2 consumed in 0.022 s.
Request queue: 1 GT + 2 VIP = 3. Added VIP room request. Produced: 2 GT + 4 VIP = 6 in 0.032 s.
...
```

Check `sample_output.txt` for complete log of production and consumption events.

Future Improvements

    Add dynamic logging levels (e.g., debug, info, error).
    Extend functionality to simulate additional resource types or thread behaviors.
    Improve performance for larger-scale simulations with more threads.

## Author

@kchan5071

## Contributor

@ayuyamo
