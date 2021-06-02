CC = clang

CFLAGS  = -g -Wall

TARGET = game
  
all: $(TARGET)
  
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 