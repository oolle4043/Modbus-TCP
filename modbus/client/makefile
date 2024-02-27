CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = client
SRCS = main.c run.c print.c function_code_01.c function_code_02.c function_code_03.c function_code_04.c function_code_05.c function_code_06.c function_code_15.c function_code_16.c
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
