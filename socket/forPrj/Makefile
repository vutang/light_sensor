LDLIBS = -lzed -lpthread
all: build

build:
	gcc -Llib/ -o client client.c $(LDLIBS)

clean:
	rm client