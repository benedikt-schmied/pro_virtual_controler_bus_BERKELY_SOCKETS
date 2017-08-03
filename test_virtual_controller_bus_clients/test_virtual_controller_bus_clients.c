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
 *      Author: Benedikt Schmied
 *
 *  Copyright (C) 2017	Benedikt Schmied
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

