CXX = g++
CXXFLAGS = -Wall -g


all: submission

submission: submission.o 
	$(CXX) $(CXXFLAGS) submission.o -o submission

submission.o: submission.cpp
	$(CXX) $(CXXFLAGS) -c submission.cpp

run: clean submission
	./submission input.txt output.txt

clean:
	rm -f *.o submission