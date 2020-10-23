#
#gcc flags
FLAGS  = -std=c99
CFLAGS += -g
#CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror

# valgrind flags
VFLAGS  = --quiet
VFLAGS += -v
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1
VFLAGS += --show-reachable=yes
VFLAGS += --show-possibly-lost=yes
VFLAGS += --undef-value-errors=yes

# targets
test: sysfs_test.out pin_test.out
	@echo "=======================\n"
	@echo "TESTING SYSFS MODULE...\n"
	@./sysfs_test.out
	@echo
	@echo "=======================\n"
	@echo "TESTING PIN MODULE...\n"
	@./pin_test.out 
	@echo
	@echo "=======================\n"



memcheck: pin_test.out sysfs_test.out poll
	@valgrind $(VFLAGS) ./pin_test.out ./sysfs_test.out ./poll_test.out
		@echo "Memory check passed"

clean:
	rm -rf *.o *.out *.out.dSYM
	./scripts/teardown.sh

poll_test.out: src/poll.c
	@echo Compiling $@
	@gcc $(CFLAGS) src/poll.c -o poll_test.out

poll: poll_test.out
	@./scripts/setup.sh
	@./poll_test.out
	@./scripts/teardown.sh

pin_test.out: src/pin.c test/test_pin.c 
	@echo Compiling $@
	@gcc $(CFLAGS) src/pin.c src/sysfs.c test/vendor/unity.c test/test_pin.c -o pin_test.out

sysfs_test.out: src/sysfs.c test/test_sysfs.c
	@echo Compiling $@
	@gcc $(CFLAGS) src/sysfs.c test/vendor/unity.c test/test_sysfs.c -o sysfs_test.out

