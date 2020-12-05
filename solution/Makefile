CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
NAME = solution

all: boyer-moore.o zfunc.o
	$(CXX) $(CXXFLAGS) boyer-moore.o zfunc.o main.cpp -o $(NAME)
boyer-moore.o: boyer-moore.cpp boyer-moore.hpp zfunc.hpp
	$(CXX) $(CXXFLAGS) -c boyer-moore.cpp
zfunc.o: zfunc.hpp
	$(CXX) $(CXXFLAGS) -c zfunc.cpp
clean:
	rm -f *.o $(NAME)