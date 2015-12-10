/*-
 * Copyright (c) 2015
 * All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>

void
memcpy(void *dst, const void *src, int len)
{
	const char *s = src;
	char *d = dst;

	while (len--)
		*d++ = *s++;
}

void
memset(void *b, int c, size_t len)
{
	char *bp = b;

	while (len--)
		*bp++ = (unsigned char)c;
}

int
memcmp(const void *b1, const void *b2, size_t len)
{
	const unsigned char *p1, *p2;

	for (p1 = b1, p2 = b2; len > 0; len--, p1++, p2++) {
		if (*p1 != *p2)
			return ((*p1) - (*p2));
	}
	return (0);
}

int
strcmp(const char *s1, const char *s2)
{

	for (; *s1 == *s2 && *s1 != '\0'; s1++, s2++)
		;
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int
strncmp(const char *s1, const char *s2, size_t len)
{

	for (; len > 0 && *s1 == *s2 && *s1 != '\0'; len--, s1++, s2++)
		;
	return (len == 0 ? 0 : (unsigned char)*s1 - (unsigned char)*s2);
}

void
strcpy(char *dst, const char *src)
{

	while (*src != '\0')
		*dst++ = *src++;
	*dst = '\0';
}

void
strcat(char *dst, const char *src)
{

	while (*dst != '\0')
		dst++;
	while (*src != '\0')
		*dst++ = *src++;
	*dst = '\0';
}

char *
strchr(const char *s, char ch)
{

	for (; *s != '\0'; s++) {
		if (*s == ch)
			return ((char *)(uintptr_t)(const void *)s);
	}
	return (NULL);
}

size_t
strlen(const char *s)
{
	size_t len = 0;

	while (*s++ != '\0')
		len++;
	return (len);
}
