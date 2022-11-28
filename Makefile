PRJ=main
CC=c++
CXXFLAGS=-std=c++11
main:
	$(CC) -g -Wall -Wextra $(CXXFLAGS) -o $@ $(PRJ).cpp -l simlib
clean:
	rm -f *.o $(PRJ)