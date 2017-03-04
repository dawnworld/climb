#include "utils/array.h"

void** alloc_2d_array(uint32 r, uint32 c, uint32 size)
{
	void* chunk = NULL;
	void** array = NULL;
	uint32 i = 0;
	uint32 *row = NULL;

	if(0 == r || 0 == c || 0 == size)
		return NULL;

	if(NULL == (chunk = MALLOC( r * c * size)))
		goto error;

	if(NULL == (array = (void **)MALLOC(r * sizeof(void *))))
		goto error;

	for(i = 0; i < r; i++)
		array[i] = (char *)chunk + i * c * size;

    return array;

error:
	if(NULL != chunk)
		FREE(chunk);

	if(NULL != array)
		FREE(array);

	return NULL;
}

void free_2d_array(void** array)
{
	if(NULL == array)
		return;

    FREE(array[0]);
    FREE(array);
}
