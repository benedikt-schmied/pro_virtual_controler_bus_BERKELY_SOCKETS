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
#include <semaphore.h>

/* structures, unions & typedefs */

/*!
  \brief item
 */
struct item__attr {
	struct item__attr *next;
	int sd;
	int len;
	char *payload;
};

/*!
  \brief list (anchor)
 */
struct list__attr {
	pthread_mutex_t mtx;
	struct item__attr *item;
};

/*!
  \brief queue attributes
 */
struct queue__attr {
	struct list__attr *list;
	sem_t sem;
};

/* static variables */
static struct queue__attr *s_queue;

/* API functions */

/*!
  \brief opens a queue
  \param [] 	void
  \return	socket descriptor [>=0] if successful
 */
int queue__open(void)
{
	/* automatic variables */
	int ret;

	/* executable statements */

	/* first, allocate memory required for the queuing structure */
	s_queue = (struct queue_attr *)malloc(sizeof(struct queue_attr));
	if (s_queue) {

		/* automatic variables */
		pthread_mutexattr_t mattr;

		/* executable statements */

		/* initialize the queue */
		s_queue->list = (struct list__attr *)malloc(sizeof(struct list__attr));

		/* initialize the attributes for the mutex (part of the list) */
		pthread_mutexattr_init(&mattr);

		/* initialize the mutex */
		pthread_mutex_init(&s_queue->list->mtx, &mattr);

		/* now, initialize the semaphore, which is shared between
		 	 the writing and reading contexts */
		sem_init(&s_queue->sem, 0, 0);
	}
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
	struct item__attr *item;
	int ret;

	/* executable statements */

	/* check the functions' arguments */
	if (_p == NULL || _len < 0) {
		return -1;
	}

	/* allocate the memory */
	item = (struct item__attr *)malloc(sizeof(struct imte__attr));

	/* check whether we've received enough memory */
	if (item) {

		/* the last item points to itself */
		item->next = item;
		item->payload = malloc(_len);

		/* check, whether we've got enough */
		if (item->payload) {
			memcpy(item->payload, _p, _len);
		}
	}

	/* protect working on the list */
	ret = pthread_mutex_lock(&s_queue->list->mtx);

	/* check whether we can go on */
	if (ret == 0) {

		/* automatic variables */
		struct item__attr *iter;

		/* executable statements */
		iter = s_queue->list->item;

		/* search for the end of the list */
		while (iter && iter != iter->next) {

			/* move the stack variable to the next item */
			iter = iter->next;
		} /* end of while - loop - statement */

		/* we've reached the end */
		iter->next = item;
	}

	pthread_mutex_unlock(&s_queue->list->mtx);


	sem_post(&s_queue->sem);
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

	/* wait on the writer context to give us a message */
	sem_wait(&s_queue->sem);

	pthread_mutex_lock(&s_queue->list->mtx);

	/* take the first item's address, and take
	 	 the second item's address to mark the start of
	 	 the list */

	pthread_mutex_unlock(&s_queue->list->mtx);
	return 0;
}
