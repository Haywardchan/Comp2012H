# Definition of variables
OBJS	= temperature_accessors.o temperature_mutators.o temperature_constructors.o temperature_test.o

# the build target executable:
TARGET = temperature_test

# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most compiler warnings
#  -pedantic complains about anything that does not adhere to the standard
CFLAGS  = -std=c++11 -Wall -pedantic

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

temperature_accessors.o: temperature.h temperature_accessors.cpp
	$(CC) $(CFLAGS) -c temperature_accessors.cpp

temperature_constructors.o: temperature.h temperature_constructors.cpp
	$(CC) $(CFLAGS) -c temperature_constructors.cpp

temperature_mutators.o: temperature.h temperature_mutators.cpp
	$(CC) $(CFLAGS) -c temperature_mutators.cpp

temperature_test.o: temperature.h temperature_test.cpp
	$(CC) $(CFLAGS) -c temperature_test.cpp

# $(RM) is defined implicitly in makefile as rm -f
clean:
	$(RM) $(OBJS) core *.core

