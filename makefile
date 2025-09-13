CXX = g++
CXXFLAGS = -Wall -g


all: submission

submission: submission.o sort.o binary-search.o
	$(CXX) $(CXXFLAGS) submission.o sort.o binary-search.o -o submission

submission.o: submission.cpp sort.h binary-search.h
	$(CXX) $(CXXFLAGS) -c submission.cpp

sort.o: sort.cpp sort.h
	$(CXX) $(CXXFLAGS) -c sort.cpp

binary-search.o: binary-search.cpp binary-search.h
	$(CXX) $(CXXFLAGS) -c binary-search.cpp

run: clean submission
	./submission input.txt output.txt

test: clean submission
	./submission test_input.txt test_output.txt test

clean:
	rm -f *.o submission