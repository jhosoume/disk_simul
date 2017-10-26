CC = g++
CFLAGS = -std=c++11 -pedantic -g -Wall -O3

INCLUDES = -I.
#LIBS=-lm add lib math


#SRCS = virtualbeing.cpp population.cpp populate.cpp
#DEPS = btree.hpp virtualbeing.hpp population.hpp
SRCS = helper.cpp disk.cpp emulate.cpp
DEPS = helper.hpp disk.hpp
OBJS = $(SRCS:.cpp=.o)

MAIN = emulate

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

disk.o: helper.hpp disk.hpp 
teste.o: helper.hpp disk.hpp 
