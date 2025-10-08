CXXFLAGS=-std=c++20 -Wall -Wextra

all: echo_server timers_example

echo_server: echo_server.cpp
	g++ $(CXXFLAGS) -o echo_server echo_server.cpp

timers_example: timers_example.cpp
	g++ $(CXXFLAGS) -o timers_example timers_example.cpp
