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


test: test_sysfs.out
		@./test_sysfs.out

memcheck: tests.out
		@valgrind $(VFLAGS) ./tests.out
			@echo "Memory check passed"

clean:
		rm -rf *.o *.out *.out.dSYM

test_pin: $(TEST_PIN)
	@echo Compiling $@
	@gcc $(CFLAGS) $(TEST_PIN) -o test_pin.out

test_sysfs.out: src/sysfs/sysfs.c test/test_sysfs.c
	@echo Compiling $@
	@gcc $(CFLAGS) src/sysfs/sysfs.c test/vendor/unity.c test/test_sysfs.c -o test_sysfs.out
