/*
 * queue.h
 *
 * This component does not have its own context. Hence create it!
 *
 *  Created on: Jul 30, 2017
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
 *
 */

#ifndef PRO_VIRTUAL_CONTROLLER_BUS_BERKELEY_SOCKETS_QUEUE_H_
#define PRO_VIRTUAL_CONTROLLER_BUS_BERKELEY_SOCKETS_QUEUE_H_

/* standard includes */
#include <stdint.h>
#include <stdlib.h>

/*!
  \brief opens a queue
  \param []     void
  \return    socket descriptor [>=0] if successful
 */
int queue__open(void);

/*!
  \brief opens a queue
  \param []     void
  \return    socket descriptor [>=0] if successful
 */
int queue__close(void);

/*!
  \brief add to the tail of a queue
  \param []     _sd     socket descriptor
  \param [in]   *_p     payload
  \param []     _len    length of data
  \return    socket descriptor [>=0] if successful
 */
int queue__add_to(int _sd, char *_p, int _len);

/*!
  \brief add to the tail of a queue
  \param []         _sd        socket descriptor
  \param [out]      **_p    address of the payload pointer
  \param [out]      *_len    address of length of data
  \return    socket descriptor [>=0] if successful
 */
int queue__remove_from(int *_sd, char **_p, int *_len);


#endif /* PRO_VIRTUAL_CONTROLLER_BUS_BERKELEY_SOCKETS_QUEUE_H_ */
