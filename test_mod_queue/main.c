/*
 * main.c
 *
 * normally we would employ embUnit, but as time is
 * short on this project we will simply call some
 * functions from the queuing modules and check the return
 * values as well as whether we can fetch everything we've
 * added before.
 *
 *  Created on: Jul 31, 2017
 *      Author: bensch
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <queue.h>

/* macros */
#define M_TEST_QUEUE__ASSERT_INT(expected, actual) \
    if (expected != actual) { \
        printf("%s failed, expected was %i, but return variable holds %i", __FUNCTION__, expected, actual); \
        return; \
    }

/* type definitions */
typedef void (*test_case)(void);

/* structure which will hold the various test cases */
struct test_case__attr {
    char const *const name;
    test_case fun;
};

void test_open(void) {

    /* automatic variables */
    int ret;

    /* executable statements */

    /* open the queue  */
    ret = queue__open();
    M_TEST_QUEUE__ASSERT_INT(0, ret);

    return;
}

void test_close(void) {

    /* automatic variables */
    int ret;

    /* executable statements */

    /* open the queue  */
    ret = queue__close();
    M_TEST_QUEUE__ASSERT_INT(0, ret);

    return;
}

int main(int argc, char *argv[])
{
    /* automatic variables */
    int ret, icnt;
    struct test_case__attr test_list [] = {
            {"test_open", test_open},
            {"test_close", test_close},
            {"test_open", test_open},
            {"test_close", test_close},
    };

    /* executable statements */

    /* print to stdout that we start testing */
    printf("this is the queuing tester\n");

    /* loop over all test cases */
    for (icnt = 0; icnt < sizeof(test_list) / sizeof(*test_list); icnt++) {
        printf("%s running\n", test_list[icnt].name);
        test_list[icnt].fun();
    } /* end of for - loop - statement */





    return 0;
}
