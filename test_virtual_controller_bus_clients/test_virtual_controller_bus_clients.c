// client.c
// https://computing.llnl.gov/tutorials/pthreads/

/* standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/* threading library */
#include <pthread.h>

/* projects' header files */
#include "unified_sockets.h"


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

/*!
  \brief starts a test client
  \param []     argc        number of arguments
  \param [in]   *argv[]    list of pointers to the arguments
                            note that the first argument is
                            the function name
  \return    0
 */
int main(int argc, char *argv[])
{
    /* automatic variables */
    int sd, ret;

    /* executable statements */

    sd = unified_sockets__open();

    /* check whether the returned socket is valid */
    if (sd) {

        /* automatic variables */

        /* executable statements */
        ret = unified_sockets__connect(sd);
        if (ret >= 0) {

            /* automatic variables */
            unsigned cnt;
            int len;
            char rbuf[1024];
            char sbuf[1024];

            /* executable statements */

            /* debugging message */
            printf("Client sending 'hello server!' to server\n");

            /* memset the entire buffer on stack */
            memset(rbuf, 0x00, sizeof(rbuf));
            memset(sbuf, 0x00, sizeof(sbuf));

            /* transfer the test string onto it */
            strncpy(sbuf, "test!\0", 20);

            /* now calculate the test string */
            len = strlen(sbuf);

            /* additionally, add the instance number onto it */
            snprintf(sbuf + len, sizeof(sbuf) - len, " instance %s", argv[1]);
            printf("%s\n", sbuf);

            /* start a loop for sending our messages */
            for (cnt = 0; cnt < 100; cnt++) {

                /* automatic variables */

                /* executable statements */

                printf("write returns %i\n", unified_sockets__send(sd, sbuf, strlen(sbuf)));
                memset(rbuf, 0x00, sizeof(rbuf));
                usleep(10000);
                int count = unified_sockets__recv(sd, rbuf, 1000);
                printf("I'm %s, Got echo of %s from server\n", argv[1], rbuf);
            } /* end of for - loop - statement */
        }
    }
//    shutdown(sd, 0);
}

