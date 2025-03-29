CC = gcc
CFLAGS = -Iinclude
SRC = src/main.c src/metrics.c src/utils.c
OUT = app1

work:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)