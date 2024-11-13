# Compiler and flags
CXX = g++
CFLAGS = -std=c++11 -g -pthread
C = gcc

# PROGRAM executable
PROGRAM = dineseating

# Declare object files
OBJECTS = log.o monitor.o producer.o consumer.o dineseating.o

# Build PROGRAM executable
$(PROGRAM): $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o $(PROGRAM)

# Compile object files
log.o: log.c
	$(C) log.c -o log.o -c

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
	rm -f $(OBJECTS) $(PROGRAM)

# Run the program
run:
	make clean
	make
	./$(PROGRAM) -s 100 -x 20 -r 35 -g 15 -v 10
	make clean
