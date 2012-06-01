/*
 * 
 */

#ifndef __ABEGEN_H
#define __ABEGEN_H

#include <stdint.h>

typedef	uint32_t u32;
typedef	int32_t s32;

#define ARRAY_SIZE(x)	(sizeof(x) / sizeof(x[0]))

struct abe_firmware {
	
	/* combined DMEM, CMEM, PMEM, SMEM */
	const uint32_t *text;
	int size;

	/* TODO: we can split the memory regions to save space */
};


struct abe_coeff_elem {

	const int32_t *coeffs;
	int size;
	const char *description;
};

#define ABE_COEFF(text, c) \
	{.description = text, \
	.coeffs = c, \
	.size = ARRAY_SIZE(c)}

struct abe_coeff {
	const char *description;
	int count;
	struct abe_coeff_elem coeff[];
};


#endif
