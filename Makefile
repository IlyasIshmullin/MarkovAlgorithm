all: markov

markov: markov.cpp
	g++ markov.cpp -o markov

clean:
	rm -rf markov *.o
