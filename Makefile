# gcc flags
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

# modules
PIN = src/pin/pin.c
SYSFS = src/sysfs/sysfs.c
UNITY = test/vendor/unity.c

# test modules
TEST_PIN = $(UNITY) + $(PIN)
TEST_PIN += test/test_pin.c

TEST_SYSFS = $(UNITY) + $(SYSFS)
TEST_SYSFS += test/test_sysfs.c


test: sysfs_test.out pin_test.out
	@echo
	@echo Running test suite..
	@echo
	@./sysfs_test.out
	@./pin_test.out 

memcheck: pin_test.out 
	@valgrind $(VFLAGS) ./pin_test.out
		@echo "Memory check passed"

clean:
	rm -rf *.o *.out *.out.dSYM

pin_test.out: src/pin/pin.c test/test_pin.c 
	@echo Compiling $@
	@gcc $(CFLAGS) src/pin/pin.c src/sysfs/sysfs.c test/vendor/unity.c test/test_pin.c -o pin_test.out

sysfs_test.out: src/sysfs/sysfs.c test/test_sysfs.c
	@echo Compiling $@
	@gcc $(CFLAGS) src/sysfs/sysfs.c test/vendor/unity.c test/test_sysfs.c -o sysfs_test.out
