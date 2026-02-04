all: producer consumer

producer:
	g++ producer.cpp -o producer.o

consumer:
	g++ consumer.cpp -o consumer.o

clean:
	rm -f producer consumer *.o

format:
	clang-format -i -style=Google producer.cpp consumer.cpp
