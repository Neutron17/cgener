#ifndef _NTR_ARGS_H_
#define _NTR_ARGS_H_ 1
#include <stdbool.h>

enum GenType {
	G_C
};

struct Args {
	enum GenType type;
	char dirName[32];
	char projName[16];
	bool isDebug;
};

struct Args parseArgs(int argc, char *argv[]);

#endif //_NTR_ARGS_H_
