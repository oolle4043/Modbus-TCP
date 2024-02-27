CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = server
SRCS = main.c close_sigint.c modbus_global.c run.c
OBJS = $(SRCS:.c=.o)
INCLUDES = -I.
LIBS = -lmodbus

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
