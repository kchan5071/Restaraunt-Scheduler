
compile:
	gcc log.c -o log.o -c
	g++ -std=c++11 log_helper.cpp -o log_helper.o -g -c
	g++ -std=c++11 producer.cpp -o producer.o -g -pthread -c
	g++ -std=c++11 consumer.cpp -o consumer.o -g -pthread -c
	g++ -std=c++11 monitor.cpp -o monitor.o -g -pthread -c


	g++ -std=c++11 dineseating.cpp producer.o consumer.o monitor.o log.o log_helper.o -o dineseating -g -pthread

clean:
	rm -f *.o

run:
	make clean
	make compile
	./dineseating -s 100 -x 20 -r 35 -g 15 -v 10
	make clean

