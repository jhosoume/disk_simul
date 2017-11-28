CC = g++
CFLAGS = -std=c++11 -pedantic -g -Wall -O3

INCLUDES = -I.
#LIBS=-lm add lib math


#SRCS = virtualbeing.cpp population.cpp populate.cpp
#DEPS = btree.hpp virtualbeing.hpp population.hpp
SRCS = helper.cpp disk.cpp my_drive.cpp
DEPS = constants.hpp helper.hpp disk.hpp
OBJS = $(SRCS:.cpp=.o)

MAIN = my_drive 

.PHONY: depend clean
all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

depend: $(SRCS)
	makedepend $(INCLUDES) $^

.PHONY: clean

clean:
	rm -f *.o $(MAIN) 
# DO NOT DELETE

disk.o: disk.hpp 
teste.o: disk.hpp 
