CC		= gcc
CFLAGS	= -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
CFLAGS += -ldl

VFLAGS	= --quiet
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

build: sysfs.o poll.o pin.o localdb.o raingauge.o mqtt_messages.o
	@echo "Building raingauge..."
	@echo Done


## library builds

sysfs.o: lib/sysfs.c lib/sysfs.h
	$(CC) -c $(CFLAGS) -o build/$@ $<

poll.o: lib/poll.c lib/poll.h
	$(CC) -c $(CFLAGS) -o build/$@ $<

pin.o: lib/pin.c lib/pin.h
	$(CC) -c $(CFLAGS) -o build/$@ $<

localdb.o: lib/localdb.c lib/localdb.h
	$(CC) -c $(CFLAGS) -o build/$@ $< -lsqlite3

mqtt_messages.o: lib/mqtt_messages.c lib/mqtt_messages.h
	$(CC) -c $(CFLAGS) -o build/$@ $<

raingauge.o: lib/raingauge.c lib/raingauge.h
	$(CC) -c $(CFLAGS) -o build/$@ $<


## test suite

test: test_localdb.out test_sysfs.out test_pin.out test_mqtt_messages.out
	@printf "\nTESTING LOCALDB MODULE...\n"
	@./build/test/test_localdb.out
	@printf "\nTESTING SYSFS MODULE...\n"
	@./build/test/test_sysfs.out
	@printf "\nTESTING PIN MODULE...\n"
	@./build/test/test_pin.out
	@printf "\nTESTING MQTT_MESSAGES MODULE...\n"
	@./build/test/test_mqtt_messages.out

test_localdb.out: test/unity.c test/test_localdb.c lib/localdb.c
	@$(CC) $(CFLAGS) -o build/test/$@ $^ -lsqlite3

test_sysfs.out: test/unity.c test/test_sysfs.c lib/sysfs.c
	@$(CC) $(CFLAGS) -o build/test/$@ $^

test_pin.out: test/unity.c test/test_pin.c lib/pin.c lib/sysfs.c lib/poll.c
	@$(CC) -pthread $(CFLAGS) -o build/test/$@ $^ 

test_mqtt_messages.out: test/unity.c test/test_mqtt_messages.c lib/mqtt_messages.c
	@$(CC) $(CFLAGS) -o build/test/$@ $^ 

## static analysis and memory checking

memcheck: test_localdb.out test_sysfs.out test_pin.out
	@valgrind $(VFLAGS) build/test/test_localdb.out
	@valgrind $(VFLAGS) build/test/test_sysfs.out
	@valgrind $(VFLAGS) build/test/test_pin.out
	@valgrind $(VFLAGS) build/test/test_mqtt_messages.out


clean:
	rm -rf build/*.o build/*.a build/*.out build/test/*.out build/test/*.o build/test/*.a
