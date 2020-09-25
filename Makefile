FLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror

VFLAGS  = --quiet
VFLAGS += -v
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1
VFLAGS += --show-reachable=yes


test: tests.out
		@./tests.out

memcheck: tests.out
		@valgrind $(VFLAGS) ./tests.out
			@echo "Memory check passed"

clean:
		rm -rf *.o *.out *.out.dSYM

tests.out: test/test_sysfs_gpio.c src/sysfs_gpio.c src/sysfs_gpio.h
		@echo Compiling $@
			@gcc $(CFLAGS) src/sysfs_gpio.c test/vendor/unity.c test/test_sysfs_gpio.c -o tests.out
