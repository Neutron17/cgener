#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "stdext.h"
#include "args.h"
#include "defaults.h"
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	struct Args args = parseArgs(argc, argv);
	if(((args.sets & 0b1) != 0b1) || ((args.sets & 0b100) != 0b100) || ((args.sets & 0b10) != 0b10))
		return 1;
	int ret = mkdir(args.dirName, S_IRWXU);
	if(ret == -1 && errno != EEXIST) {
		fprintf(stderr, "Error in creating directory: %s, %s\n", args.dirName, strerror(errno));
		return 1;
	}
	/*if(!isDir(args.dirName)) {
		fprintf(stderr, "Was not a directory\n");
		return 1;
	}*/
	char tmpdirName[24];
	strncpy(tmpdirName, args.dirName, 16);
	char str[420];
	{
		char before[420];
		strncpy(str, MakefileDef, 420);
		char *after = strstr(str, "                ");
		strncpy(before, str, strlen(str) - strlen(after));
		before[strlen(str) - strlen(after)] = '\0';
		sprintf(str, "%s%s", before, after);
	}
	FILE *file = fopen(strncat(tmpdirName,"/Makefile", 24), "w");
	strncpy(tmpdirName, args.dirName, 16);
	if(!file) {
		fprintf(stderr, "Couldn't open Makefile\n");
		return 2;
	}
	fprintf(file, "%420s", str);
	ret = mkdir(strcat(tmpdirName, "/build/"), S_IRWXU);
	if (ret == -1) {
		fprintf(stderr, "Error in creating directory: %s, %s\n", tmpdirName, strerror(errno));
		if(errno != EEXIST)
			exit(EXIT_FAILURE);
	}
	strncpy(tmpdirName, args.dirName, 16);
	ret = mkdir(strncat(tmpdirName, "/src/", 22), S_IRWXU);
	if (ret == -1) {
		fprintf(stderr, "Error in creating directory: %s, %s\n", tmpdirName, strerror(errno));
		if(errno != EEXIST)
			exit(EXIT_FAILURE);
	}
	strncpy(tmpdirName, args.dirName, 16);

	fclose(file);
	return EXIT_SUCCESS;
}

