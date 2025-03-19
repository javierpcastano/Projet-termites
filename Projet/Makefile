CXX=g++
CXXFLAGS= -std=c++11 -Wall 

EXEC_FILES= test projet 

all: projet

coord.o : coord.cpp coord.hpp
	$(CXX) $(CXXFLAGS) -c $< 
    
grille.o : grille.cpp grille.hpp coord.hpp
	$(CXX) $(CXXFLAGS) -c $<

termite.o : termite.cpp termite.hpp grille.hpp coord.hpp
	$(CXX) $(CXXFLAGS) -c $<

projet.o: projet.cpp coord.hpp grille.hpp termite.hpp
	$(CXX) $(CXXFLAGS) -c $<

test.o : test.cpp coord.hpp grille.hpp termite.hpp
	$(CXX) $(CXXFLAGS) -c $<

test: test.o coord.o grille.o termite.o
	$(CXX) -o test $^

projet: projet.o grille.o coord.o termite.o
	$(CXX) -o projet $^
      
check: test
	./test -s

clean : 
	rm -f *.o $(EXEC_FILES)
