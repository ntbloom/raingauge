#include <assert.h>
#include <fcntl.h>
#include <poll.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../lib/constants.h"
#include "../lib/pin.h"
#include "../lib/poll.h"
#include "../lib/sysfs.h"
#include "unity.h"

#define SLEEP_SECONDS 5

void setUp(void) {
    /* pass
     *
     */
}
void tearDown(void) {
    /* pass
     *
     */
}

/* basic test of the constructor, run `make memtest` to confirm memory safety*/
void test_construct_pin(void) {
    size_t num = 18;
    Pin* pin_ptr = construct_pin(num);
    TEST_ASSERT_NOT_NULL(pin_ptr);

    const char* desc = "/sys/class/gpio/gpio18";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(desc, pin_ptr->desc, "bad desc");

    const char* direc = "/sys/class/gpio/gpio18/direction";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(direc, pin_ptr->direc, "bad direct");

    const char* value = "/sys/class/gpio/gpio18/value";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(value, pin_ptr->value, "bad value");

    const char* edge = "/sys/class/gpio/gpio18/edge";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(edge, pin_ptr->edge, "bad edge");

    const char* active_low = "/sys/class/gpio/gpio18/active_low";
    TEST_ASSERT_EQUAL_STRING_MESSAGE(active_low, pin_ptr->active_low, "bad active_low");

    deconstruct_pin(pin_ptr);
}

/* make sure constructor turns on pin and deconstructor turns it off */
void test_automatic_export_unexport(void) {
    size_t num = 18;
    Pin* pin_ptr = construct_pin(num);
    TEST_ASSERT_NOT_NULL(pin_ptr);

    const char* gpio18 = "/sys/class/gpio/gpio18";
    TEST_ASSERT_MESSAGE(file_exists(gpio18, F_OK, 1) == EXIT_SUCCESS, "pin not exported");

    deconstruct_pin(pin_ptr);
    fprintf(stderr, "\texpected test error message: ");
    TEST_ASSERT_MESSAGE(file_exists(gpio18, F_OK, 1) == EXIT_FAILURE, "pin not unexported");
}

/* check that the constructor/desctructor works with all legal pins, 0 through 26
 * inclusive except GPIO4.
 */
void test_all_legal_pins(void) {
    for (int i = 0; i <= MAX_PIN; i++) {
        Pin* pin_ptr = construct_pin(i);

        /* pin 4 not legal on pi3b */
        if (i == 4) {
            TEST_ASSERT_NULL(pin_ptr);
            continue;
        }

        char* err = malloc(50);
        sprintf(err, "problem exporting pin %d", i);
        TEST_ASSERT_MESSAGE(file_exists(pin_ptr->desc, W_OK, 1) != EXIT_FAILURE, err);
        TEST_ASSERT_MESSAGE(file_exists(pin_ptr->value, W_OK, 1) != EXIT_FAILURE, err);
        TEST_ASSERT_MESSAGE(file_exists(pin_ptr->direc, W_OK, 1) != EXIT_FAILURE, err);
        free(err);
        deconstruct_pin(pin_ptr);
    }
}

/* test the infinite loop poll */
struct thread_data {
    Pin* gauge;
    Pin* stop_rx;
    Pin* stop_tx;
    int thread_id;
};
void* _poll_thread(void* t) {
    int poll;
    struct thread_data* data;

    data = (struct thread_data*)t;
    printf("\nMANUALLY TESTING GAUGE SWITCH FOR %d SECONDS...\n", SLEEP_SECONDS);
    poll = poll_loop(data->gauge->value, data->stop_rx->value, NULL);
    TEST_ASSERT_EQUAL(poll, EXIT_SUCCESS);

    pthread_exit((void*)t);
}
void* _kill_loop(void* t) {
    int kill;
    struct thread_data* data;
    data = (struct thread_data*)t;

    sleep(SLEEP_SECONDS);
    kill = write_to_file(data->stop_tx->value, LOW);
    TEST_ASSERT_EQUAL(kill, EXIT_SUCCESS);

    pthread_exit((void*)t);
}
void test_poll_loop(void) {
    int setup, cleanup;
    Pin *gauge_rx, *stop_rx, *stop_tx;
    int tid = 0;
    pthread_t thread[2];
    pthread_attr_t attr;
    int rc0, rc1, j0, j1;

    gauge_rx = construct_pin(GAUGE_RX);
    stop_rx = construct_pin(STOP_RX);
    stop_tx = construct_pin(STOP_TX);

    TEST_ASSERT_NOT_NULL(gauge_rx);
    TEST_ASSERT_NOT_NULL(stop_tx);
    TEST_ASSERT_NOT_NULL(stop_rx);

    setup = prep_pin(gauge_rx, IN, RISING, HIGH) | prep_pin(stop_rx, IN, BOTH, LOW) |
            prep_pin(stop_tx, OUT, NONE, LOW);
    TEST_ASSERT_EQUAL(setup, EXIT_SUCCESS);

    struct thread_data data = {
        .gauge = gauge_rx,
        .stop_rx = stop_rx,
        .stop_tx = stop_tx,
        .thread_id = tid,
    };

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    rc0 = pthread_create(&thread[0], NULL, _poll_thread, (void*)&data);
    tid++;
    rc1 = pthread_create(&thread[1], NULL, _kill_loop, (void*)&data);
    TEST_ASSERT_EQUAL(rc0 | rc1, EXIT_SUCCESS);

    pthread_attr_destroy(&attr);
    j0 = pthread_join(thread[0], NULL);
    j1 = pthread_join(thread[1], NULL);
    TEST_ASSERT_EQUAL(j0 | j1, EXIT_SUCCESS);

    cleanup = deconstruct_pin(gauge_rx) | deconstruct_pin(stop_rx) | deconstruct_pin(stop_tx);
    TEST_ASSERT_EQUAL(cleanup, EXIT_SUCCESS);
}

int main(void) {
    UnityBegin("test/test_pin.c");

    RUN_TEST(test_construct_pin);
    RUN_TEST(test_automatic_export_unexport);
    RUN_TEST(test_all_legal_pins);
    RUN_TEST(test_poll_loop);

    UnityEnd();

    pthread_exit(NULL);
    return EXIT_SUCCESS;
}
