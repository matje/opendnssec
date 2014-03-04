/*
 * Copyright (c) 2014 NLNet Labs. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *
 * String utilities.
 */

#include "config.h"
#include "strfunc.h"

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE (16 * 1024) /* use 16K buffers */

static unsigned int file_count = 0;


/**
 * Compare strings.
 *
 */
int
ods_strcmp(const char* s1, const char* s2)
{
    if (!s1 && !s2) {
        return 0;
    } else if (!s1) {
        return -1;
    } else if (!s2) {
        return -1;
    } else if (strlen(s1) != strlen(s2)) {
        if (strncmp(s1, s2, strlen(s1)) == 0) {
            return strlen(s1) - strlen(s2);
        }
    }
    return strncmp(s1, s2, strlen(s1));
}


/**
 * Compare a string lowercased
 *
 */
int
ods_strlowercmp(const char* str1, const char* str2)
{
    while (str1 && str2 && *str1 != '\0' && *str2 != '\0') {
        if (tolower((int)*str1) != tolower((int)*str2)) {
            if (tolower((int)*str1) < tolower((int)*str2)) {
                return -1;
            }
            return 1;
        }
        str1++;
        str2++;
    }
    if (str1 && str2) {
        if (*str1 == *str2) {
            return 0;
        } else if (*str1 == '\0') {
            return -1;
        }
    } else if (!str1 && !str2) {
        return 0;
    } else if (!str1 && str2) {
        return -1;
    }
    return 1;
}
