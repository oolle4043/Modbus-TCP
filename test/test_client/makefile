CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = client
SRCS = main.c run.c function_code_01.c function_code_03.c
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
