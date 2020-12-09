/*
 * unified_sockets_win.c
 *
 * This is just a short and quick solution to build this
 * litte test framework on windows as well as on linux.
 * Can be replaced in future with BOOST library
 *
 *  Created on: 30.07.2017
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
#include <unified_sockets.h>
#include <queue.h>

/* static variable which holds all currently used descriptors */
static int s_pro_virtual_controller_bus_sd_tab[100] = {0};

/* points the the first empty entry */
static int *s_pro_virtual_controller_bus_sd_ptr = s_pro_virtual_controller_bus_sd_tab;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

/*!
  \brief push descriptor
  \param []     void
  \return    socket descriptor [>=0] if successful
 */
void push_descriptor(int _sd)
{
    /* automatic variables */
    int s;
    int *indic;

    /* executable statements */
    for (indic = s_pro_virtual_controller_bus_sd_tab; indic < s_pro_virtual_controller_bus_sd_ptr; indic++) {

        /* check, whether we already have fetched this socket descriptor */
        if (*indic == _sd) {
            return;
        }
    }

    /* we've came up to this stage, hence, the entry is missing, now
         search for a free entry */

    if (s_pro_virtual_controller_bus_sd_ptr != s_pro_virtual_controller_bus_sd_tab + sizeof(s_pro_virtual_controller_bus_sd_tab) / sizeof(*s_pro_virtual_controller_bus_sd_tab)) {

        /* push it onto the next free item */
        *s_pro_virtual_controller_bus_sd_ptr = _sd;

        /* move the pointer to the next empty item */
        s_pro_virtual_controller_bus_sd_ptr++;
    }
    return;
}

/*!
  \brief pop descriptor
  \param []     void
  \return    socket descriptor [>=0] if successful
 */
void pop_descriptor(int _sd)
{
    /* automatic variables */
    int s;

    /* executable statements */
}

/*!
  \brief treas incoming message
  \param []     void
  \return    socket descriptor [>=0] if successful
 */
void* treat_incoming_message(void* param)
{
    /* automatic variables */
    int s = (int)param;
    char buf[1024];
    int count;
    unsigned long mode = 0;

    /* executable statements */

//    pthread_detach(pthread_self());
    fprintf(stdout, "starting echo thread\n");

    count = unified_sockets__recv(s, buf, 1024);
    fprintf(stdout, "count %i and file descriptor %i\n", count, s);
    fflush(stdout);

    while (count > 0) {

        /* push the message into the buffer */
        queue__add_to(s, buf, count);

        fprintf(stdout, "received message on socket %i\n", s);
        fflush(stdout);

        count = unified_sockets__recv(s, buf, 1000);
    }
    if (count < 0) {
        fprintf(stdout, "recv error: %s\n", strerror(errno));
        fflush(stdout);
    }

    fprintf(stdout, "closing connection\n");
    fflush(stdout);

    close(s);
    return NULL;
}

int echo_sync(int _fd)
{
    /* automatic variables */
    char buf[1024];
    int count;
    unsigned long mode = 0;

    /* executable statements */

    count = unified_sockets__recv(_fd, buf, 1000);
    fprintf(stdout, "count %i and file descriptor %i\n", count, _fd);

    while (count >= 0) {

        fprintf(stdout, "Server received %s\n", buf);
        fprintf(stdout, "Server sending it back\n");
        fflush(stdout);
        unified_sockets__send(_fd, buf, strlen(buf));

        count = unified_sockets__recv(_fd, buf, 1000);
    }
    if (count < 0) {
        fprintf(stdout, "recv error: %s\n", strerror(errno));
        fflush(stdout);
    }
    fprintf(stdout, "closing connection\n");
    fflush(stdout);

    close(_fd);
    return 0;
}

/*!
  \brief    thread starting point, which main target is to distribute incoming
              messages to other peers

  \param [in]       _p      argument
  \return    return value
 */
void *broadcasting_messages(void *_p) {

    /* automatic variables */
    int ret, icnt, sd;
    char *p;
    int len;

    /* executable statements */

    ret = queue__remove_from(&sd, &p, &len);
    while (ret >= 0) {

        /* automatic variables */
        int *indic;

        /* executable statements */

        /* now, look into the list of descriptors and send this message
             to all other peers (sockets) */
        for (indic = s_pro_virtual_controller_bus_sd_tab; indic < s_pro_virtual_controller_bus_sd_ptr; indic++) {

            /* if the current entry is equal the senders's socket descriptor,
                 continue the loop */
            if (*indic == sd) {
                continue;
            }

            /* at this stage, send the message */
            unified_sockets__send(*indic, p, len);

        } /* end of for - loop - statement */

        /* just print a short debugging message */
        fprintf(stdout, "removed message on socket %i\n", sd);
        fflush(stdout);

        /* this storage has been allocated before, hence, free it, we do not
             need it anymore */
        free(p);

        /* before checking the loop statement again, we have to call
             the remove from function */
        ret = queue__remove_from(&sd, &p, &len);
    }
    return NULL;
}

/*!
  \brief main function

  starts the execution of the virtual controller bus server

  \param []     argc        number of arguments
  \param [in]   *argv[]     list of pointer to the arguments themselves
  \return    socket descriptor [>=0] if successful
 */
int main(int argc, char *argv[])
{
    /* automatic variables */
    int sd, newsd, ret, len;
    pthread_t pth; /* pthread handle */
    pthread_attr_t tattr; /* pthread attributes */

    /* executable statements */
    fprintf(stdout, "starting server\n");
    fflush(stdout);

    /* we need to startup the queue */
    queue__open();

    /* initialize the attributes */
    pthread_attr_init(&tattr);

    /* before we start accepting incoming connections we have to start the
         thread which takes care of the date to drop in and spreads them
         to other ports*/
    pthread_create(&pth, &tattr, broadcasting_messages, NULL);

    /* open a socket */
    sd = unified_sockets__open();
    if (sd >= 0) {

        /* bind on port */
        unified_sockets__bind(sd);

        /* listen */
        unified_sockets__listen(sd);

        /* accept incoming connection */
        newsd = unified_sockets__accept(sd);
        fflush(stdout);

        /* check, whether it is equal or larger zero */
        while (newsd) {

            /* automatic variables */
            pthread_t t;

            /* executable statements */

            /* first, push this new socket descriptor onto the list */
            push_descriptor(newsd);

            /* creates a thread which takes care of the newly accepted
                 socket */
            pthread_create(&t, 0, treat_incoming_message, (void*)newsd);

            /* wait for the next connection to pop up */
            newsd = unified_sockets__accept(sd);
        } /* end of while - loop - statement */
     }
    return 0;
}
