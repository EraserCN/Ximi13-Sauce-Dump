/*
 * Copyright (c) 2006 Ryan Martell. (rdm4@martellventures.com)
 *
 * This file is part of Libav.
 *
 * Libav is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Libav is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Libav; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVUTIL_BASE64_H
#define AVUTIL_BASE64_H

#include <stdint.h>
#include <limits.h>


/**
 * @defgroup lavu_base64 Base64
 * @ingroup lavu_crypto
 * @{
 */

typedef unsigned char uint8;


/**
 * Decode a base64-encoded string.
 *
 * @param out      buffer for decoded data
 * @param in       null-terminated input string
 * @param out_size size in bytes of the out buffer, must be at
 *                 least 3/4 of the length of in
 * @return         number of bytes written, or a negative value in case of
 *                 invalid input
 */
int base64_decode(uint8 *out, const char *in, int out_size);

/**
 * Encode data to base64 and null-terminate.
 *
 * @param out      buffer for encoded data
 * @param out_size size in bytes of the output buffer, must be at
 *                 least AV_BASE64_SIZE(in_size)
 * @param in_size  size in bytes of the 'in' buffer
 * @return         'out' or NULL in case of error
 */
char *base64_encode(char *out, int out_size, const uint8 *in, int in_size);

/**
 * Calculate the output size needed to base64-encode x bytes.
 */
#define AV_BASE64_SIZE(x)  (((x)+2) / 3 * 4 + 1)


#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))

 /**
  * @}
  */

#endif /* AVUTIL_BASE64_H */
