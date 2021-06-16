CPP =  g++ -std=c++11
CPPOPTS = -fopenmp -msse -mfpmath=sse -O3 -DNDEBUG -c

CC =  gcc
CCOPTS = -fopenmp -msse -mfpmath=sse -O3 -DNDEBUG -c

LNK = g++
LNKOPTS = -O3 -fopenmp -pthread -lpthread 
HDRS = \
	src/io-handle.h \
	src/reduce.h \
	src/solver.h \
	src/util.h \


OBJS = \
	o/io-handle.o \
	o/main.o \
	o/reduce.o \
	o/solver.o \
	o/util.o \

exe : o/ $(OBJS)
	$(LNK) $(LNKOPTS) $(OBJS) -o exe
	strip -d exe
o/ :
	mkdir -p o/
o/io-handle.o : src/io-handle.cpp $(HDRS)
	$(CPP) $(CPPOPTS) -o o/io-handle.o src/io-handle.cpp
o/main.o : src/main.cpp $(HDRS)
	$(CPP) $(CPPOPTS) -o o/main.o src/main.cpp
o/reduce.o : src/reduce.cpp $(HDRS)
	$(CPP) $(CPPOPTS) -o o/reduce.o src/reduce.cpp
o/solver.o : src/solver.cpp $(HDRS)
	$(CPP) $(CPPOPTS) -o o/solver.o src/solver.cpp
o/util.o : src/util.cpp $(HDRS)
	$(CPP) $(CPPOPTS) -o o/util.o src/util.cpp

