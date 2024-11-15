compile:
	gcc log.c -o log.o -c
	g++ -std=c++11 -pthread log_helper.cpp -o log_helper.o -g -c
	g++ -std=c++11 -pthread monitor.cpp -o monitor.o -g -c
	g++ -std=c++11 -pthread producer.cpp -o producer.o -g -c
	g++ -std=c++11 -pthread consumer.cpp -o consumer.o -g -c

	g++ -std=c++11 -pthread dineseating.cpp producer.o consumer.o monitor.o log.o log_helper.o -o dineseating -g 

clean:
	rm -f dineseating
	rm -f *.o

run:
	make clean
	make compile
	./dineseating -s 10 -x 13 -r 14 -g 7s -v 12
	make clean

