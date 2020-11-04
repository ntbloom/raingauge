CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror
#CFLAGS += -c
CFLAGS += -pthread
CFLAGS += -ldl
CFLAGS += -lsqlite3

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

test: sysfs_test.out pin_test.out localdb_test.out
	@echo "=======================\n"
	@echo "TESTING SYSFS MODULE...\n"
	@./sysfs_test.out
	@echo
	@echo "=======================\n"
	@echo "TESTING PIN MODULE...\n"
	@./pin_test.out &
	@sleep 10 && echo 0 > /sys/class/gpio/gpio18/value
	@echo "=======================\n"
	@echo "TESTING LOCALDB MODULE...\n"
	@./localdb_test.out




memcheck: pin_test.out sysfs_test.out localdb_test.out poll_test.out
	@valgrind $(VFLAGS) ./sysfs_test.out 
	@valgrind $(VFLAGS) ./pin_test.out &
	@sleep 15 && echo 0 > /sys/class/gpio/gpio18/value
	@valgrind $(VFLAGS) ./localdb_test.out
	@echo "Memory check passed"

clean:
	rm -rf *.o *.out *.out.dSYM

localdb_test.out: src/localdb.c
	@echo Compiling $@
	@gcc $(CFLAGS) src/localdb.c test/vendor/unity.c test/test_localdb.c -o localdb_test.out

poll_test.out: src/poll.c
	@echo Compiling $@
	@gcc $(CFLAGS) src/poll.c -o poll_test.out

poll: poll_test.out
	@./scripts/setup.sh
	@./poll_test.out
	@./scripts/teardown.sh

pin_test.out: src/pin.c test/test_pin.c 
	@echo Compiling $@
	@gcc $(CFLAGS) src/pin.c src/sysfs.c src/poll.c test/vendor/unity.c test/test_pin.c -o pin_test.out

sysfs_test.out: src/sysfs.c test/test_sysfs.c
	@echo Compiling $@
	@gcc $(CFLAGS) src/sysfs.c test/vendor/unity.c test/test_sysfs.c -o sysfs_test.out

raingauge.out:
	@echo Compiling $@
	@gcc $(CFLAGS) src/* -o raingauge.out
