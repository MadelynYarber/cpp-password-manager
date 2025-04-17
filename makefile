CXX=g++
CXXFLAGS=-Wall -pedantic

proj5.x: proj5.cpp passserver.h passserver.cpp hashtable.h hashtable.hpp
	$(CXX) $(CXXFLAGS) -lcrypt -o proj5.x proj5.cpp passserver.cpp

.SUFFIXES: .x

.PHONY : clean

clean:
	rm -f *.o *.x *.gch core.* 
