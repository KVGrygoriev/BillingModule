VERSION=0.0.1
CC=g++
TARGET=BillingSystemTest

LIBS=-lBillingSystem
RFLAGS= -std=c++11 -DNDEBUG -O2

INCLUDES=-I. -I../BillingSystem/include/ -I../Additions/cxxtest-4.4/
LIB_PATH=../BillingSystem/lib

OPTFLAGS=$(RFLAGS)
CCFLAGS=$(OPTFLAGS) $(INCLUDES)

CPPS=$(wildcard *.cpp)
OBJS=$(CPPS:.cpp=.o)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

$(TARGET): $(OBJS) 
	$(CC) $(OBJS) $(INCLUDES) -L$(LIB_PATH) $(LIBS) -o $@

clean:
	$(RM) $(OBJS) $(TARGET)
