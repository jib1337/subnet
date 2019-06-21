# Subnet Calculator | Jack Nelson
# Build the binard

CC = gcc
CFLAGS = -Wall -lm
SOURCE = subnet.c
EXEC = subnet

$(EXEC): $(OBJ)
	$(CC) $(SOURCE) -o $(EXEC) $(CFLAGS)

