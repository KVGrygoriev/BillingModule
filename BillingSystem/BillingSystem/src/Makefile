
VERSION=0.0.1
CC=g++
TARGET=BillingSystem
TARGET_LIB=libBillingSystem.a

RFLAGS= -std=c++11 -DNDEBUG -O2

INCLUDES=-I. -I../include

OPTFLAGS=$(RFLAGS)
CCFLAGS=$(OPTFLAGS) $(INCLUDES)

CPPS=$(wildcard *.cpp)
OBJS=$(CPPS:.cpp=.o)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

${TARGET_LIB} : $(OBJS)
	ar -rv ${TARGET_LIB} $(OBJS) $@
	mv ${TARGET_LIB} ../lib

clean:
	$(RM) $(OBJS) $(TARGET)

