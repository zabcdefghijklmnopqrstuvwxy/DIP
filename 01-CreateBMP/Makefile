CC:=gcc
INCLUDE:=-I.
CXXFLAGS:=-Wall -g -std=c99
LDFLAGS:=

SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %c,%o,$(SRCS))

TARGET:=bmp

.PHONY:all clean

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS):%o:%c
	$(CC) -c $^ -o $@ $(CXXFLAGS) $(INCLUDE)

clean:
	rm -fr $(OBJS) $(TARGET)
