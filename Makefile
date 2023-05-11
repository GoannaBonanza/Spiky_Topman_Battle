CXX=g++
CXXFLAGS=-Wall -O3 -Wextra -Wpedantic
Spiky_Topman_Boss: main.o Begoman.o KMP.o
	$(CXX) $(CXXFLAGS) main.o Begoman.o KMP.o -o Spiky_Topman_Boss
main.o: main.cc Begoman.h KMP.h
	$(CXX) $(CXXFLAGS) -c main.cc
Begoman.o: Begoman.h Begoman.cc
	$(CXX) $(CXXFLAGS) -c Begoman.cc
KMP.o: KMP.h KMP.cc
	$(CXX) $(CXXFLAGS) -c KMP.cc
clean:
	rm -f *.o Spiky_Topman_Boss
