
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
    exit(1);
}

void* echo(void* param)
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

    	printf("Server received %s\n", buf);
        printf("Server sending it back\n");
        unified_sockets__send(s, buf, strlen(buf));

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

int main(int argc, char *argv[])
{
	/* automatic variables */
	int sd, newsd, ret, len;

	/* executable statements */
	sd = unified_sockets__open();
	if (sd >= 0) {

		/* bind on port */
		unified_sockets__bind(sd);

		/* listen */
		unified_sockets__listen(sd);

		/* accept incoming connection */
		newsd = unified_sockets__accept(sd);

		/* check, whehter it is equal or larger zero */
		while (newsd) {
			pthread_t t;
			pthread_create(&t, 0, echo, (void*)newsd);
			newsd = unified_sockets__accept(sd);
		} /* end of while - loop - statement */
	 }
	return 0;
}
