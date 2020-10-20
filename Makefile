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

memcheck: pin_test.out sysfs_test.out
	@valgrind $(VFLAGS) ./pin_test.out ./sysfs_test.out
		@echo "Memory check passed"

clean:
	rm -rf *.o *.out *.out.dSYM

poll: 
	@gcc $(CFLAGS) poll_throwaway.c -o poll_throwaway.out
	@./poll_throwaway.out

pin_test.out: src/pin/pin.c test/test_pin.c 
	@echo Compiling $@
	@gcc $(CFLAGS) src/pin/pin.c src/sysfs/sysfs.c test/vendor/unity.c test/test_pin.c -o pin_test.out

sysfs_test.out: src/sysfs/sysfs.c test/test_sysfs.c
	@echo Compiling $@
	@gcc $(CFLAGS) src/sysfs/sysfs.c test/vendor/unity.c test/test_sysfs.c -o sysfs_test.out
