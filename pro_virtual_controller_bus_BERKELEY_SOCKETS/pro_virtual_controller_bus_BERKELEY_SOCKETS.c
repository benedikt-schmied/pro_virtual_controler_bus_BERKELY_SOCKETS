
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

void error(const char *msg)
{
    perror(msg);
    exit(1);
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

    pthread_detach(pthread_self());
    printf("starting echo thread\n");

    count = unified_sockets__recv(s, buf, 1024);
    printf("count %i and file descriptor %i\n", count, s);

    while (count >= 0) {

        /* push the message into the buffer */
        queue__add_to(s, buf, count);

        count = unified_sockets__recv(s, buf, 1000);
    }
    if (count < 0) {
        printf("recv error: %s\n", strerror(errno));
    }


    printf("closing connection\n");

    close(s);
}

int echo_sync(int _fd)
{
    /* automatic variables */
    char buf[1024];
    int count;
    unsigned long mode = 0;

    /* executable statements */

    count = unified_sockets__recv(_fd, buf, 1000);
    printf("count %i and file descriptor %i\n", count, _fd);

    while (count >= 0) {

        printf("Server received %s\n", buf);
        printf("Server sending it back\n");
        unified_sockets__send(_fd, buf, strlen(buf));

        count = unified_sockets__recv(_fd, buf, 1000);
    }
    if (count < 0) {
        printf("recv error: %s\n", strerror(errno));
    }
    printf("closing connection\n");

    close(_fd);
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

        /*  */


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
    printf("starting server\n");

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

        /* check, whether it is equal or larger zero */
        while (newsd) {

            /* automatic variables */
            pthread_t t;

            /* executable statements */

            /* creates a thread which takes care of the newly accepted
                 socket */
            pthread_create(&t, 0, treat_incoming_message, (void*)newsd);

            /* wait for the next connection to pop up */
            newsd = unified_sockets__accept(sd);
        } /* end of while - loop - statement */
     }
    return 0;
}
