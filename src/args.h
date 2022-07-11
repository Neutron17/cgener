#ifndef _NTR_ARGS_H_
#define _NTR_ARGS_H_ 1
#include <stdbool.h>
#include "template.h"

struct GenType {
	char path[32];
	Template type;
	bool isValid;
};

struct Args {
	Template type;
	char dirName[32];
	char projName[16];
	unsigned char sets;
	bool isDebug;
};

struct Args parseArgs(int argc, char *argv[]);

#endif //_NTR_ARGS_H_
