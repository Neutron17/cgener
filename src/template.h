#ifndef _NTR_TEMPLATE_H_
#define _NTR_TEMPLATE_H_ 1
#include "array.h"

typedef struct File File;

struct File {
	char name[16];
	bool isFile;
	Array children;
};

File *file_create(const char *, bool, Array);

File loadTemplate(const char *name);

#endif //_NTR_TEMPLATE_H_

