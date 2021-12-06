#include <stdlib.h>
#include <string.h>

void* calloc(size_t nmemb, size_t size)
{
	uint64_t required_size = nmemb
		* size;
	size_t request_size = (size_t)required_size;

	if (request_size != required_size)  return NULL;
	size_t cnt = nmemb * size;
	void* pt = (void*)malloc(request_size);
	if (pt != NULL)
		memset(pt, 0, cnt);
	return pt;
}