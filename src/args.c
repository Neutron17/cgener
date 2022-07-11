#include "args.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "template.h"
#include "common.h"

struct Args parseArgs(int argc, char *argv[]) {
	struct Args ret;
	int c;
	// Bits: 1st - dir, 2nd - projName, 3rd - type  
	unsigned char sets = 0;
	while((c = getopt(argc, argv, "vVdho:n:p:t:")) != -1){
		switch(c) {
			case 'h':
				printf(
			"Boilerplate Generator\n"
			"\t-h: help\n"
			"\t-v: version\n"
			"\t-V -d: Verbose and debug\n"
			"\t-o <ditectory name>: Directory for the project to be created\n"
			"\t-p, -n <project name>: project name, by default the same as the directory name(-o)\n"
			"\t-t <name>: template name by which the project will be generated, placed in 'templates/' dorectory\n");
				break;
			case 'V':
			case 'd':
				ret.isDebug = true;
				break;
			case 'v':
				printf("Version %d.%d.%d\n"
			,VERSION_1,VERSION_2,VERSION_3);
				exit(0);
			case 'o':
				strncpy(ret.dirName,
					optarg, 32);
				sets |= 0b1;
				break;
			case 'p':
			case 'n':
				strncpy(ret.projName,
					optarg, 16);
				sets |= 0b10;
				break;
			case 't':
				loadTemplate(optarg);
				sets |= 0b100;
				break;
		}
	}
	ret.sets = sets;
	return ret;
//	return (struct Args) { G_C, "foo", "foo", false };
}
