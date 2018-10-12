
CC=gcc
AR=ar

LIB=libzed
LIB_OBJS = logger.o
LIB_HEADERS = logger.h
HEADER_FILES = logger.h
CFLAGS = -fPIC

all: build install
build: $(LIB).a $(LIB).so

install:
	ln -s $(PWD)/$(LIB).so.1.0.1 $(PWD)/$(LIB).so
	ln -s $(PWD)/$(LIB).so.1.0.1 $(PWD)/$(LIB).so.1


$(LIB).a:$(LIB_OBJS) 
	$(AR) rcs $@ $(LIB_OBJS)

$(LIB).so:$(LIB_OBJS) 
	$(CC) -shared -o $@.1.0.1 $(LIB_OBJS)

%.o: %.c $(HEADER_FILES)
	$(CC) -c $(CFLAGS) -o $@ $<


clean: 
	rm *.o
	rm libzed*