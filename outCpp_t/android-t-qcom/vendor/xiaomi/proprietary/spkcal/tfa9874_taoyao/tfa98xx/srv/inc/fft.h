/* 
 * Free FFT and convolution (C)
 * 
 * Copyright (c) 2016 Project Nayuki
 * https://www.nayuki.io/page/free-small-fft-in-multiple-languages
 * 
 * (MIT License)
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * - The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * - The Software is provided "as is", without warranty of any kind, express or
 *   implied, including but not limited to the warranties of merchantability,
 *   fitness for a particular purpose and noninfringement. In no event shall the
 *   authors or copyright holders be liable for any claim, damages or other
 *   liability, whether in an action of contract, tort or otherwise, arising from,
 *   out of or in connection with the Software or the use or other dealings in the
 *   Software.
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>
#if !(defined(WIN32) || defined(_X64)) // LINUX!
#include <stdbool.h>
#ifndef __ANDROID__  // Not Android
#include <tgmath.h>
#endif // !__ANDROID__
#else // Windows
#if !defined (bool) || !defined(__BOOL_DEFINED)
	  typedef unsigned char bool;
	  #define true ((bool)(1==1))
	  #define false ((bool)(1==0))
	#define __BOOL_DEFINED
#endif
#endif // !(defined(WIN32) || defined(_X64))


#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif 

/* 
 * Computes the discrete Fourier transform (DFT) of the given complex vector, storing the result back into the vector.
 * The vector can have any length. This is a wrapper function. Returns true if successful, false otherwise (out of memory).
 */
bool transform(double real[], double imag[], size_t n);

/* 
 * Computes the inverse discrete Fourier transform (IDFT) of the given complex vector, storing the result back into the vector.
 * The vector can have any length. This is a wrapper function. This transform does not perform scaling, so the inverse is not a true inverse.
 * Returns true if successful, false otherwise (out of memory).
 */
bool inverse_transform(double real[], double imag[], size_t n);

/* 
 * Computes the discrete Fourier transform (DFT) of the given complex vector, storing the result back into the vector.
 * The vector's length must be a power of 2. Uses the Cooley-Tukey decimation-in-time radix-2 algorithm.
 * Returns true if successful, false otherwise (n is not a power of 2, or out of memory).
 */
bool transform_radix2(double real[], double imag[], size_t n);

/* 
 * Computes the discrete Fourier transform (DFT) of the given complex vector, storing the result back into the vector.
 * The vector can have any length. This requires the convolution function, which in turn requires the radix-2 FFT function.
 * Uses Bluestein's chirp z-transform algorithm. Returns true if successful, false otherwise (out of memory).
 */
bool transform_bluestein(double real[], double imag[], size_t n);

/* 
 * Computes the circular convolution of the given real vectors. Each vector's length must be the same.
 * Returns true if successful, false otherwise (out of memory).
 */
bool convolve_real(const double x[], const double y[], double out[], size_t n);

/* 
 * Computes the circular convolution of the given complex vectors. Each vector's length must be the same.
 * Returns true if successful, false otherwise (out of memory).
 */
bool convolve_complex(const double xreal[], const double ximag[], const double yreal[], const double yimag[], double outreal[], double outimag[], size_t n);
