CXXFLAGS=-std=c++23 -Wall -Wextra

all: echo_co_server echo_server timers_example

echo_co_server: echo_co_server.cpp
	g++ $(CXXFLAGS) -o echo_co_server echo_co_server.cpp

echo_server: echo_server.cpp
	g++ $(CXXFLAGS) -o echo_server echo_server.cpp

timers_example: timers_example.cpp
	g++ $(CXXFLAGS) -o timers_example timers_example.cpp
