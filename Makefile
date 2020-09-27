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

UNITY = test/vendor/unity.c

PINTEST = $(UNITY)
PINTEST += src/pin.c
PINTEST += src/pin.h

SRC += test/test_pin.c
SRC += test/test_sysfs.c

TESTS = test/test_sysfs.c
TESTS += test/test_pin.c
TESTS += src/pin.h
TESTS += src/pin.c
TESTS += src/sysfs.h
TESTS += src/sysfs.c



test: tests.out pin_tests
		@./tests.out

memcheck: tests.out
		@valgrind $(VFLAGS) ./tests.out
			@echo "Memory check passed"

clean:
		rm -rf *.o *.out *.out.dSYM

tests.out: $(TESTS)
		@echo Compiling $@
			@gcc $(CFLAGS) $(SRC) -o tests.out

pin_tests.out: $(PINTESTS)
	@echo Compiling $@
	@gcc $(CFLAGS) $(PINSRC) -o pin_tests.out

sysfs_tests.out: $(SYSFSTESTS)
	@echo Compiling $@
	@gcc $(CFLAGS) $(SYSFSSRC) -o sysfs_tests.out
