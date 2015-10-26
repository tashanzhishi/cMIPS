CC = gcc
CFLAGS = -Wall -O -g
TARGET = cMIPS

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

SOURCES = $(wildcard src/*.c)
OBJS = $(patsubst %.c,%.o,$(SOURCES))

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	chmod a+x $(TARGET)

clean:
	rm -rf *.o src/*.o
cleanall:
	rm -rf *.o src/*.o $(TARGET)
