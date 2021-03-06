/* Copyright (c) 2018, Tom Schoonjans
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    * The names of the contributors may not be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY Tom Schoonjans ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Tom Schoonjans BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "xraylib.h"
#include "xraylib-error-private.h"
#include <assert.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv) {
	xrl_error *error = NULL;
	double rate, yield;

	rate = AugerRate(82, K_L3M5_AUGER, &error);
	assert(fabs(rate - 0.004573193387) < 1E-6);
	assert(error == NULL);
	
	rate = AugerRate(82, L3_M4N7_AUGER, &error);
	assert(fabs(rate - 0.0024327572005) < 1E-6);
	assert(error == NULL);
	
	rate = AugerRate(-35, L3_M4N7_AUGER, &error);
	assert(rate == 0.0);
	assert(error != NULL);
	assert(error->code == XRL_ERROR_INVALID_ARGUMENT);
	assert(strcmp(error->message, Z_OUT_OF_RANGE) == 0);
	xrl_clear_error(&error);
	
	rate = AugerRate(82, M4_M5Q3_AUGER + 1, &error);
	assert(rate == 0.0);
	assert(error != NULL);
	assert(error->code == XRL_ERROR_INVALID_ARGUMENT);
	assert(strcmp(error->message, UNKNOWN_AUGER) == 0);
	xrl_clear_error(&error);
	
	rate = AugerRate(62, L3_M4N7_AUGER, &error);
	assert(rate == 0.0);
	assert(error != NULL);
	assert(error->code == XRL_ERROR_INVALID_ARGUMENT);
	assert(strcmp(error->message, INVALID_AUGER) == 0);
	xrl_clear_error(&error);
	
	yield = AugerYield(82, K_SHELL, &error);
	assert(error == NULL);
	assert(fabs(yield - (1.0 - FluorYield(82, K_SHELL, NULL))) < 1E-6);
	
	yield = AugerYield(82, M3_SHELL, &error);
	assert(error == NULL);
	assert(fabs(yield - 0.1719525) < 1E-6);
	
	yield = AugerYield(82, L1_SHELL, &error);
	assert(error == NULL);
	assert(fabs(yield - 0.1825) < 1E-9);
	
	yield = AugerYield(-35, K_SHELL, &error);
	assert(yield == 0.0);
	assert(error != NULL);
	assert(error->code == XRL_ERROR_INVALID_ARGUMENT);
	assert(strcmp(error->message, Z_OUT_OF_RANGE) == 0);
	xrl_clear_error(&error);
	
	yield = AugerYield(82, N2_SHELL, &error);
	assert(yield == 0.0);
	assert(error != NULL);
	assert(error->code == XRL_ERROR_INVALID_ARGUMENT);
	assert(strcmp(error->message, UNKNOWN_SHELL) == 0);
	xrl_clear_error(&error);
	
	yield = AugerYield(26, M5_SHELL, &error);
	assert(yield == 0.0);
	assert(error != NULL);
	assert(error->code == XRL_ERROR_INVALID_ARGUMENT);
	assert(strcmp(error->message, INVALID_SHELL) == 0);
	xrl_clear_error(&error);

	return 0;	
}

