compile:
	gcc log.c -o log.o -c
	g++ -std=c++11 producer.cpp log.o -o producer.o -g -pthread -c
	g++ -std=c++11 general_producer.cpp log.o -o general_producer.o -g -pthread -c
	g++ -std=c++11 VIP_producer.cpp log.o -o VIP_producer.o -g -pthread -c
	g++ -std=c++11 monitor.cpp log.o -o monitor.o -g -pthread -c


	g++ -std=c++11 dineseating.cpp producer.o general_producer.o VIP_producer.o monitor.o log.o -o dineseating.o -g -pthread

clean:
	rm -f *.o

run:
	make clean
	make compile
	./dineseating.o -s 10

