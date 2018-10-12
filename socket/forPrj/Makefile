
TAR=client.elf
LDLIBS = -lzed -lpthread

SRC = client.c

all: build

build:
	gcc -Llib/ -o $(TAR) $(SRC) $(LDLIBS)

clean:
	rm $(TAR) *.o