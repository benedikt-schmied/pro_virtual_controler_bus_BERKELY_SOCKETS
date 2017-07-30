/*
 * queue.c
 *
 * Internally, this components works on lists, we simply
 * push new items to the tail. We will emply malloc routines
 * in order to request memory and release it layer. Send to
 * queue will emit a signal, or send a semaphore which is
 * received by the 'remove_from' - function
 *
 *  Created on: Jul 30, 2017
 *      Author: Benedikt Schmied
 */

/* standard includes */
#include <stdint.h>
#include <stdlib.h>

/* threading component */
#include <pthread.h>

/*!
  \brief opens a queue
  \param [] 	void
  \return	socket descriptor [>=0] if successful
 */
int queue__open(void)
{
	/* automatic variables */

	/* executable statements */

	return 0;
}

/*!
  \brief opens a queue
  \param [] 	void
  \return	socket descriptor [>=0] if successful
 */
int queue__close(void)
{
	/* automatic variables */

	/* executable statements */
	return 0;
}

/*!
  \brief add to the tail of a queue
  \param [] 	_sd		socket descriptor
  \param [in] 	*_p		payload
  \param []		_len	length of data
  \return	socket descriptor [>=0] if successful
 */
int queue__add_to(int _sd, char *_p, int _len)
{
	/* automatic variables */

	/* executable statements */
	return 0;
}

/*!
  \brief add to the tail of a queue
  \param [] 	_sd		socket descriptor
  \param [out] 	**_p	address of the payload pointer
  \param [out]	*_len	address of length of data
  \return	socket descriptor [>=0] if successful
 */
int queue__remove_from(int _sd, char **_p, int *_len)
{
	/* automatic variables */

	/* executable statements */
	return 0;
}
