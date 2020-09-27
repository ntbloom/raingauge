FLAGS  = -std=c99
CFLAGS += -g
#CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror

VFLAGS  = --quiet
VFLAGS += -v
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1
VFLAGS += --show-reachable=yes

SRC = test/vendor/unity.c
SRC += src/pin.c
#uSRC += test/test_pin.c
SRC += test/test_sysfs.c

TESTS = test/test_sysfs.c
#TESTS += test/test_pin.c
TESTS += src/pin.h
#TESTS += src/pin.c
TESTS += src/sysfs.h
TESTS += src/sysfs.c

test: tests.out
		@./tests.out

memcheck: tests.out
		@valgrind $(VFLAGS) ./tests.out
			@echo "Memory check passed"

clean:
		rm -rf *.o *.out *.out.dSYM

tests.out: $(TESTS)
		@echo Compiling $@
			@gcc $(CFLAGS) $(SRC) -o tests.out
