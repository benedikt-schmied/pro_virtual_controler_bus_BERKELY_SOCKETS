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

int main(int argc, char *argv[])
{
	/* automatic variables */
    int sd, ret;

    /* executable statements */

    sd = unified_sockets__open();
    if (sd) {

    	/* automatic variables */

    	/* executable statements */
    	ret = unified_sockets__connect(sd);
    	if (ret >= 0) {

    		/* automatic variables */
			unsigned cnt;
			int len;

			/* executable statements */
			printf("Client sending 'hello server!' to server\n");
			char buf[1024];
			memset(buf, 0x00, sizeof(buf));
			strncpy(buf, "test!\0", 20);
			len = strlen(buf);
			snprintf(buf + len, sizeof(buf) - len, " instance %s", argv[1]);
			printf("%s\n", buf);

			for (cnt = 0; cnt < 10; cnt++) {

				/* automatic variables */

				/* executable statements */

				printf("write returns %i\n", unified_sockets__send(sd, buf, strlen(buf)));
				memset(buf, 0x00, sizeof(buf));
				int count = unified_sockets__recv(sd, buf, 1000);
				printf("I'm %s, Got echo of %s from server\n", argv[1], buf);
			}
    	}
    }
	shutdown(sd, 0);
}
