CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic
NAME = benchmark
DIR = ../solution

all: boyer-moore.o zfunc.o
	$(CXX) $(CXXFLAGS) boyer-moore.o zfunc.o benchmark.cpp -o $(NAME)
boyer-moore.o: $(DIR)/boyer-moore.cpp $(DIR)/boyer-moore.hpp $(DIR)/zfunc.hpp
	$(CXX) $(CXXFLAGS) -c $(DIR)/boyer-moore.cpp
zfunc.o: $(DIR)/zfunc.hpp
	$(CXX) $(CXXFLAGS) -c $(DIR)/zfunc.cpp
clean:
	rm -f *.o $(NAME)