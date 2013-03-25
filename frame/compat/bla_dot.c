/*

   BLIS    
   An object-based framework for developing high-performance BLAS-like
   libraries.

   Copyright (C) 2013, The University of Texas

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    - Neither the name of The University of Texas nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "blis.h"


//
// Define BLAS-to-BLIS interfaces.
//
#undef  GENTFUNCDOT
#define GENTFUNCDOT( ftype, chxy, chc, blis_conjx, blasname, blisname ) \
\
ftype PASTEF772(chxy,blasname,chc)( \
                                    fint*   n, \
                                    ftype*  x, fint* incx, \
                                    ftype*  y, fint* incy \
                                  ) \
{ \
	dim_t  n0; \
	ftype* x0; \
	ftype* y0; \
	inc_t  incx0; \
	inc_t  incy0; \
	ftype  rho; \
\
	/* Convert negative values of n to zero. */ \
	bli_convert_blas_dim1( *n, n0 ); \
\
	/* If the input increments are negative, adjust the pointers so we can
	   use positive increments instead. */ \
	bli_convert_blas_incv( n0, x, *incx, x0, incx0 ); \
	bli_convert_blas_incv( n0, y, *incy, y0, incy0 ); \
\
	/* Call BLIS interface. */ \
	PASTEMAC3(chxy,chxy,chxy,blisname)( blis_conjx, \
	                                    BLIS_NO_CONJUGATE, \
	                                    n0, \
	                                    x0, incx0, \
	                                    y0, incy0, \
	                                    &rho ); \
\
	return rho; \
}

#ifdef BLIS_ENABLE_BLAS2BLIS
INSERT_GENTFUNCDOT_BLAS( dot, DOTV_KERNEL )


// -- "Black sheep" dot product function definitions --

float PASTEF77(sd,sdot)( fint*  n,
                         float* x, fint* incx,
                         float* y, fint* incy
                       )
{
	bli_check_error_code( BLIS_NOT_YET_IMPLEMENTED );

	return 0.0F;
}

double PASTEF77(d,sdot)( fint*  n,
                         float* x, fint* incx,
                         float* y, fint* incy
                       )
{
	bli_check_error_code( BLIS_NOT_YET_IMPLEMENTED );

	return 0.0;
}

#endif
