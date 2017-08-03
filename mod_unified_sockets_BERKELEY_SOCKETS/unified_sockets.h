/*
 * unified_sockets_unix.h
 *
 * This is just a short and quick solution to build this
 * litte test framework on windows as well as on linux.
 * Can be replaced in future with BOOST library
 *
 *  Created on: 30.07.2017
 *      Author: B. Schmied
 *
 */

#ifndef VA_APP_TEST_BUS_MASTER_BERKELY_SOCKETS_UNIFIED_SOCKETS_H_
#define VA_APP_TEST_BUS_MASTER_BERKELY_SOCKETS_UNIFIED_SOCKETS_H_

/* defines */
#define M_TEST__PORT_NUMBER        9999
#define M_TEST__IP_ADDR            "127.0.0.1"
/*!
  \brief open a socket
  \param void
  \return socket (descriptor)
*/
int unified_sockets__open(void);

/*!
  \brief connects to a socket
  \param []        _sd        socket descriptor
  \return successful if equal zero
 */
int unified_sockets__connect(int _sd);

/*!
  \brief receives from a socket
  \param []        _sd        socket descriptor
  \param [in]    *_p        buffer
  \param []        _len    (maximum) length of buffer
  \return successful if equal zero
 */
int unified_sockets__bind(int _sd);

/*!
  \brief receives from a socket
  \param []        _sd        socket descriptor
  \param [in]    *_p        buffer
  \param []        _len    (maximum) length of buffer
  \return new socket descriptor if successful [>0]
 */
int unified_sockets__accept(int _sd);

/*!
  \brief receives from a socket
  \param []        _sd        socket descriptor
  \return new socket descriptor if successful [>0]
 */
int unified_sockets__listen(int _sd);

/*!
  \brief sends to a socket
  \param []        _sd        socket descriptor
  \param [in]    *_p        buffer
  \param []        _len    effective length of buffer
  \return successful if equal zero
 */
int unified_sockets__send(int _sd, char *_p, int _len);

/*!
  \brief receives from a socket
  \param []        _sd        socket descriptor
  \param [in]    *_p        buffer
  \param []        _len    (maximum) length of buffer
  \return successful if equal zero
 */
int unified_sockets__recv(int _sd, char *_p, int _len);

/*!
  \brief closes a socket, no matter whether it sends, receives or does both
  \param []        _sd        socket descriptor
  \param [in]    *_p        buffer
  \param []        _len    (maximum) length of buffer
  \return successful if equal zero
 */
int unified_sockets__close(int _sd);

#endif /* VA_APP_TEST_BUS_MASTER_BERKELY_SOCKETS_UNIFIED_SOCKETS_H_ */

