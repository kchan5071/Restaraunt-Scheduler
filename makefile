#Makefile

# Specify compiler
CC = g++
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb 
CCFLAGS = -std=c++11 -Wall -g3 -c

# object files
OBJS = log_helper.o log.o dineseating.o consumer.o producer.o monitor.o

# Program name
PROGRAM = dineseating

# The program depends upon its object files
$(PROGRAM) : $(OBJS)
	$(CC) -pthread -o $(PROGRAM) $(OBJS)

dineseating.o : dineseating.cpp
	$(CC) $(CCFLAGS) dineseating.cpp

consumer.o : consumer.cpp consumer.h
	$(CC) $(CCFLAGS) consumer.cpp

producer.o: producer.cpp producer.h
	$(CC) $(CCFLAGS) producer.cpp

monitor.o: monitor.cpp monitor.h
	$(CC) $(CCFLAGS) monitor.cpp

log_helper.o: log_helper.cpp log_helper.h
	$(CC) $(CCFLAGS) log_helper.cpp

log.o: log.c log.h
	gcc log.c -o log.o -c

clean :
	rm -f $(OBJS) *~ $(PROGRAM)
run:
	make clean
	make
	# ./$(PROGRAM) 
	# ./$(PROGRAM) 
	# ./$(PROGRAM) 
	# ./$(PROGRAM) 
	# ./$(PROGRAM) 
	# ./$(PROGRAM) 
	# ./$(PROGRAM) 
	# ./$(PROGRAM) 
	./$(PROGRAM) 
	./$(PROGRAM) 
	./$(PROGRAM) 
	./$(PROGRAM) -v 3 -g 9 -x 37 -r 40
	./$(PROGRAM) -s 5
	./$(PROGRAM) -s 5 -v 10 -g 25 -x 2 -r 3
	./$(PROGRAM) 1
	./$(PROGRAM) -v 2000 -g 1 -x 3 -r 7
	./$(PROGRAM) 1
	./$(PROGRAM) -s 120
	./$(PROGRAM) -s 150
	./$(PROGRAM) -s 75
	./$(PROGRAM) -v 1 -g 2 -x 30 -r 30
	./$(PROGRAM) -v 2 -g 1 -x 3 -r 3
	./$(PROGRAM) -v 2 -g 3 -x 1 -r 1
	./$(PROGRAM) -v 2 -g 4 -x 1 -r 5
	./$(PROGRAM) -v 1 -g 2 -x 3 -r 4
	make clean

