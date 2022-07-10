#include "args.h"

struct Args parseArgs(int argc, char *argv[]) {
	return (struct Args) { G_C, "foo", "foo", false };
}
