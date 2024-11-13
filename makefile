# Compiler and flags
CXX = g++
CFLAGS = -std=c++11 -g -pthread
C = gcc

# Target executable
TARGET = dineseating

# Source and object files
SOURCES = log.c monitor.cpp log_helper.cpp producer.cpp consumer.cpp  dineseating.cpp
OBJECTS = log.o monitor.o log_helper.o producer.o consumer.o dineseating.o

# Build target executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Compile object files
log.o: log.c
	$(C) log.c -o log.o -c

log_helper.o: log_helper.cpp
	$(CXX) $(CFLAGS) -c log_helper.cpp -o log_helper.o

monitor.o: monitor.cpp
	$(CXX) $(CFLAGS) -c monitor.cpp -o monitor.o

producer.o: producer.cpp
	$(CXX) $(CFLAGS) -c producer.cpp -o producer.o

consumer.o: consumer.cpp
	$(CXX) $(CFLAGS) -c consumer.cpp -o consumer.o


dineseating.o: dineseating.cpp
	$(CXX) $(CFLAGS) -c dineseating.cpp -o dineseating.o

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the program
run:
	make clean
	make
	./$(TARGET) -s 100 -x 20 -r 35 -g 15 -v 10
	make clean
