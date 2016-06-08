/* 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 only,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License version 2 for more details (a copy is included
 * in the LICENSE file that accompanied this code).
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

/*
 * Copyright (c) 2016, Thomas Stibor <t.stibor@gsi.de>
 */

#ifndef LOG_H
#define LOG_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/time.h>
#include <linux/limits.h>

#define UNUSED(x) (void)(x)

/* Bottom three bits reserved for api_message_level. */
#define API_MSG_MASK		0x00000007
#define API_MSG_NO_ERRNO	0x00000010

enum api_message_level {
	API_MSG_OFF    = 0,
	API_MSG_FATAL  = 1,
	API_MSG_ERROR  = 2,
	API_MSG_WARN   = 3,
	API_MSG_NORMAL = 4,
	API_MSG_INFO   = 5,
	API_MSG_DEBUG  = 6,
	API_MSG_MAX
};

int api_msg_get_level(void);
void api_msg_set_level(int level);
void api_error(enum api_message_level level, int err, const char *fmt, ...);
double ct_now(void);

#define CT_ERROR(_rc, _format, ...)				     \
	api_error(API_MSG_ERROR, _rc,				     \
		  "%f [%ld] %s:%d "_format,			     \
		  ct_now(), syscall(SYS_gettid), __FILE__, __LINE__, \
		  ## __VA_ARGS__)

#define CT_DEBUG(_format, ...)					     \
	api_error(API_MSG_DEBUG | API_MSG_NO_ERRNO, 0,		     \
		  "%f [%ld] %s:%d "_format,			     \
		  ct_now(), syscall(SYS_gettid), __FILE__, __LINE__, \
		  ## __VA_ARGS__)

#define CT_WARN(_format, ...)					     \
	api_error(API_MSG_WARN | API_MSG_NO_ERRNO, 0,		     \
		  "%f [%ld] %s:%d "_format,			     \
		  ct_now(), syscall(SYS_gettid), __FILE__, __LINE__, \
		  ## __VA_ARGS__)

#define CT_TRACE(_format, ...)					     \
	api_error(API_MSG_INFO | API_MSG_NO_ERRNO, 0,		     \
		  "%f [%ld] %s:%d "_format,			     \
		  ct_now(), syscall(SYS_gettid), __FILE__, __LINE__, \
		  ## __VA_ARGS__)


#endif /* LOG_H */
