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

/* includes */
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/* networking libraries */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* project's header file */
#include "unified_sockets.h"

/*!
  \brief open a socket
  \param void
  \return socket (descriptor)
*/
int unified_sockets__open(void)
{
    /* automatic variables */
    int ret;

    /* executable statements */

    /* create a socket */
    ret = socket(AF_INET, SOCK_STREAM, 0);

    /* prior of returning, make some debuggin output */
    if (ret < 0) {
        printf("socket successfully opened: %d\n", ret);
    } else {
        printf("socket successfully opened\n");
    }

    /* return the 'ret' variable which may contain the
          socket descriptor */
    return ret;
}

/*!
  \brief connects to a socket
  \param []        _sd        socket descriptor
  \return successful if equal zero
 */
int unified_sockets__connect(int _sd)
{
    /* automatic variables */
    int ret;
    struct sockaddr_in serv_addr;
    uint16_t portno;

    /* executable statements */

    /* clear address structure */
    memset((char *) &serv_addr, 0x00, sizeof(serv_addr));

    /* setup the host_addr structure for use in bind call */
    serv_addr.sin_family = AF_INET;

    /* automatically be filled with current host's IP address */
    serv_addr.sin_addr.s_addr = inet_addr(M_TEST__IP_ADDR);;

    /* assign the port number */
    portno = M_TEST__PORT_NUMBER;

    /* push it into the structure */
    serv_addr.sin_port = htons(M_TEST__PORT_NUMBER);

    /* executable statements */
    ret = connect(_sd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    switch (ret) {
    case 0:
        break;
    default:
        printf("error on connecting %i\n", ret);
        ret = -1;
        break;
    }
    return ret;
}

/*!
  \brief receives from a socket
  \param []      _sd     socket descriptor
  \param [in]    *_p     buffer
  \param []      _len    (maximum) length of buffer
  \return successful if equal zero
 */
int unified_sockets__bind(int _sd)
{
    /* automatic variables */
    int ret;
    struct sockaddr_in serv_addr;
    uint16_t portno;

    /* executable statements */

    /* clear address structure */
    memset((char *) &serv_addr, 0x00, sizeof(serv_addr));

    /* setup the host_addr structure for use in bind call */
    serv_addr.sin_family = AF_INET;

    // automatically be filled with current host's IP address
    serv_addr.sin_addr.s_addr = inet_addr(M_TEST__IP_ADDR);;

    /* assign the port number */
    portno = M_TEST__PORT_NUMBER;

    /* push it into the structure */
    serv_addr.sin_port = htons(M_TEST__PORT_NUMBER);

    // This bind() call will bind  the socket to the current IP address on port
    ret = bind(_sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    switch (ret) {
    case 0:
        break;
    default:
        printf("error on binding %i\n", ret);
        ret = -1;
        break;
    }
    return ret;
}

/*!
  \brief receives from a socket
  \param []        _sd        socket descriptor
  \return new socket descriptor if successful [>0]
 */
int unified_sockets__listen(int _sd)
{
    /* automatic variables */
    int ret;

    /* executable statements */
    ret = listen(_sd, 30);
    switch (ret) {
    case 0:
        break;
    default:
        ret = -1;
        break;
    }
    return ret;
}

/*!
  \brief receives from a socket
  \param []        _sd        socket descriptor
  \param [in]    *_p        buffer
  \param []        _len    (maximum) length of buffer
  \return new socket descriptor if successful [>0]
 */
int unified_sockets__accept(int _sd)
{
    /* automatic variables */
    int ret;
    struct sockaddr_in cli_addr;
    int len;

    /* executable statements */

    len = sizeof(cli_addr);
    ret = accept(_sd, (struct sockaddr *)&cli_addr, &len);
    if (ret >= 0) {
        ;
    } else {
        ret = -1;
    }
    return ret;
}

/*!
  \brief sends to a socket
  \param []        _sd        socket descriptor
  \param [in]    *_p        buffer
  \param []        _len    effective length of buffer
  \return successful if equal zero
 */
int unified_sockets__send(int _sd, char *_p, int _len)
{
    /* automatic variables */
    int ret;

    /* executable statements */
    ret = send(_sd, _p, _len, 0);
    if (ret >= 0) {
        ;
    } else {
        ret = -1;
    }
    return ret;
}

/*!
  \brief receives from a socket
  \param []        _sd        socket descriptor
  \param [in]    *_p        buffer
  \param []        _len    (maximum) length of buffer
  \return successful if equal zero
 */
int unified_sockets__recv(int _sd, char *_p, int _len)
{
    /* automatic variables */
    int ret;

    /* executable statements */
    ret = recv(_sd, _p, _len, 0);
    if (ret >= 0) {
        ;
    } else {
        ret = -1;
    }
    return ret;
}
