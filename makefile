compile:
	gcc log.c -o log.o -c
	g++ -std=c++11 producer.cpp log.o -o producer.o -g -pthread -c
	g++ -std=c++11 consumer.cpp log.o -o consumer.o -g -pthread -c
	g++ -std=c++11 monitor.cpp log.o -o monitor.o -g -pthread -c


	g++ -std=c++11 dineseating.cpp producer.o consumer.o monitor.o log.o -o dineseating.o -g -pthread

clean:
	rm -f *.o

run:
	make clean
	make compile
	./dineseating.o -s 10
	make clean

