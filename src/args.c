#include "args.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "template.h"
#include "common.h"

struct Args parseArgs(int argc, char *argv[]) {
	struct Args ret;
	int c;
	// Bits: 1st - dir, 2nd - projName, 3rd - type  
	unsigned char sets = 0;
	while((c = getopt(argc, argv, "vVdho:n:p:t:u:")) != -1){
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
			case 't': {
				File tmp = loadTemplate(optarg);
				printf("used: %d\n", tmp.children.used);
				//while(tmp.children.array != NULL) {
					for(int i = 0; i < tmp.children.used; i++) {
						puts("Here");
						if(((File*)tmp.children.array[i])->isFile) {
							free(tmp.children.array[i]);
						} else {
							if(((File*)tmp.children.array[i])->children.array != NULL) {
								for(int j = 0; j < ((File*)tmp.children.array[i])->children.used; j++) {
									printf("%s\n", ((File *)(((File *)tmp.children.array[i])->children.array[j]))->name);
									free((File *)(((File *)tmp.children.array[i])->children.array[j]));
								}
								array_destroy(&((File *)tmp.children.array[i])->children);
							}
						}
					}
				//}
				ret.template = tmp;
				sets |= 0b100;
			} break;
			case 'u': {
				strncpy(ret.uname, optarg, 16);
			} break;
			default:
				fprintf(stderr, "Unknown argument: '%c' for program\n", optopt);
				exit(1);
		}
	}
	if((sets & 0b1) && ((sets & 0b10) != 0b10)) {
		strncpy(ret.projName, ret.dirName, 16);
		sets |= 0b10;
	}
	ret.sets = sets;
	return ret;
//	return (struct Args) { G_C, "foo", "foo", false };
}
