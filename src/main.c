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
	if(!isDir(args.dirName)) {
		fprintf(stderr, "Was not a directory\n");
		return 1;
	}
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
	int ret = mkdir(strcat(tmpdirName, "/build/"), S_IRWXU);
	if (ret == -1) {
		switch (errno) {
			case EACCES :
				fprintf(stderr, "the parent directory does not allow write\n");
				exit(EXIT_FAILURE);
			case EEXIST:
				fprintf(stderr, "pathname: %s already exists\n", tmpdirName);
				break;
			case ENAMETOOLONG:
				fprintf(stderr, "pathname: %s is too long\n", tmpdirName);
				exit(EXIT_FAILURE);
			default:
				perror("mkdir");
				exit(EXIT_FAILURE);
		}
	}
	strncpy(tmpdirName, args.dirName, 16);
	ret = mkdir(strncat(tmpdirName, "/src/", 22), S_IRWXU);
	if (ret == -1) {
		switch (errno) {
			case EACCES :
				fprintf(stderr, "the parent directory does not allow write\n");
				exit(EXIT_FAILURE);
			case EEXIST:
				fprintf(stderr, "pathname: %s already exists\n", tmpdirName);
				break;
			case ENAMETOOLONG:
				fprintf(stderr, "pathname: %s is too long\n", tmpdirName);
				exit(EXIT_FAILURE);
			default:
				perror("mkdir");
				exit(EXIT_FAILURE);
		}
	}
	strncpy(tmpdirName, args.dirName, 16);
	fclose(file);
	return 0;
}

