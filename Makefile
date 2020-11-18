CC      = gcc
CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -pthread
CFLAGS += -ldl

VFLAGS  = --quiet
VFLAGS += -v
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1
VFLAGS += --show-reachable=yes
VFLAGS += --show-possibly-lost=yes
VFLAGS += --undef-value-errors=yes
VFLAGS += --suppressions=suppressions/custom.supp
VFLAGS += --suppressions=suppressions/sqlite3.supp
VFLAGS += --track-origins=yes
#VFLAGS += --gen-suppressions=all

.PHONY: test clean

build: sysfs.o poll.o pin.o localdb.o raingauge.o
	@echo "Building raingauge..."
	@echo Done

sysfs.o: lib/sysfs.c
	$(CC) -c $(CFLAGS) -o build/sysfs.o lib/sysfs.c 

poll.o: lib/poll.c
	$(CC) -c $(CFLAGS) -o build/poll.o lib/poll.c 

pin.o: lib/pin.c
	$(CC) -c $(CFLAGS) -o build/pin.o lib/pin.c 

localdb.o: lib/localdb.c
	$(CC) -c $(CFLAGS) -o build/localdb.o -lsqlite3 lib/localdb.c 

raingauge.o: lib/raingauge.c
	$(CC) -c $(CFLAGS) -o build/raingauge.o lib/raingauge.c 

raingauge.a: sysfs.o poll.o pin.o localdb.o raingauge.o
	ar rcs build/raingauge.a build/*.o

unity.o: test/unity.c raingauge.a
	$(CC) -c $(CFLAGS) -o build/unity.o test/unity.c -lbuild/raingauge.a

test_sysfs.out: unity.o sysfs.o
	$(CC) $(CFLAGS) -o build/test_sysfs.out build/sysfs.o test/sysfs.c 
	./build/test_sysfs.out

clean:
	rm -rf build/*.o build/*.a build/*.out
