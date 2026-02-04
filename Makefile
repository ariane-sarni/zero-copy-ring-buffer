producer:
	g++ producer.cpp -o producer.o
consumer:
	g++ consumer.cpp -o consumer.o
clean:
	rm *.o
