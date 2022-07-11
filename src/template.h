#ifndef _NTR_TEMPLATE_H_
#define _NTR_TEMPLATE_H_ 1
#include "array.h"

typedef struct {
	char name[16];
	bool isFile;
	Array children;
} File;
File *file_create(const char *, bool, Array);
typedef struct Template_t {
	char name[16];
	File dir;
} Template;

Template loadTemplate(const char *name);

#endif //_NTR_TEMPLATE_H_

