#include "template.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include "common.h"

File loadTemplate(const char *name) {
	char *templatePath = malloc(10 + strnlen(name, 16) + 7 + 1);
	sprintf(templatePath, "%s%s%s", "templates/", name, ".genert");
	FILE *templateFile = fopen(templatePath, "r");
	if (!templateFile) {
		fprintf(stderr, "Couldn't open templateFile: %s, %s\n", templatePath, strerror(errno));
		exit(1);
	}
	long length;
	fseek(templateFile, 0, SEEK_END);
	length = ftell(templateFile);
	fseek(templateFile, 0, SEEK_SET);
	char *buffer = malloc(length);
	if (!buffer) {
		fprintf(stderr, "Couldn't allocate memory for buffer while loading template, %s\n", strerror(errno));
		exit(1);
	}
	fread(buffer, 1, length, templateFile);
	fclose(templateFile);

	File ret = { "", false, array_create(10) };
	strncpy(ret.name, name, 16);
	free(templatePath);
	templatePath = NULL;
	Array dirs = array_create(10);
	char *symbol_sp, *line_sp;
	for (
			char *line = strtok_r(buffer, "\n", &line_sp);
			line != NULL;
			line = strtok_r(NULL, "\n", &line_sp)) {

		for (char *symbol = strtok_r(line, " \t", &symbol_sp);
			 symbol != NULL;
			 symbol = strtok_r(NULL, " \t", &symbol_sp)) {
			if (strncasecmp(symbol, "template", 8) == 0) {
				char *buff = malloc(18);
				char shift = 0;
				strncpy(buff, strtok_r(NULL, " \t", &symbol_sp), 18);
				if(*buff == '"') {
					buff++;
					buff[strnlen(buff, 18)-1] = '\0';
					shift++;
				}
				array_add(&dirs, (void *) (file_create("", false, array_create(3))));
				strncpy(((File *) dirs.array[0])->name, buff, 16);
				mkdir(buff, S_IRWXU);
				free(buff-shift);
			} else if (strncasecmp(symbol, "dir", 3) == 0) {
				char *buff = malloc(18);
				char bShift = 0;
				strncpy(buff, strtok_r(NULL, " \t", &symbol_sp), 18);
				if(*buff == '"') {
					buff++;
					buff[strnlen(buff, 18)-1] = '\0';
					bShift++;
				}
				//sprintf(buff, "%s", buff);
				array_add(&dirs,
						  (void *) file_create("", false, array_create(2)));
				strncpy(((File*) dirs.array[dirs.used-1])->name, buff, 16);
				free(buff-bShift);
				buff = NULL;
				char *dirpath = calloc(18, 1);
				for (int i = 0; i < dirs.used; i++) {
					strncat(dirpath, ((File *) dirs.array[i])->name, 16);
					strncat(dirpath, "/", 1);
				}
				mkdir(dirpath, S_IRWXU);
				free(dirpath);
			} else if (strncasecmp(symbol, "dend", 3) == 0) {
				free(array_last(dirs));
				array_pop(&dirs);
			} else if (strncasecmp(symbol, "file", 4) == 0) {
				char *filename = malloc(18);
				char fnShift = 0;
				strncpy(filename, strtok_r(NULL, " \t", &symbol_sp), 18);

				if(*filename == '"') {
					filename++;
					filename[strnlen(filename, 18)-1] = '\0';
					fnShift++;
				}
				char *filepath = calloc(64, 1);
#ifdef MEM_DEBUG
				memdeb_add(filepath);
#endif
				for (int i = 0; i < dirs.used; i++) {
					strncat(filepath, ((File *) dirs.array[i])->name, 16);
					strncat(filepath, "/", 1);
				}
				strncat(filepath, filename, 18);
				printf("Path: %s\n", filepath);
				FILE *file = fopen(filepath, "w");
				if(!file) {
					fprintf(stderr, "Couldn't open file: '%s': %s\n", filepath, strerror(errno));
					exit(1);
				}
				/*printf("FilePath: '%s'\n", filepath);
				printf("Written: %d\n", fprintf(file, "Hi\n"));
				fflush(file);
				getchar();*/
				free(filepath);
				filepath = NULL;
				//char *buff = calloc(512, sizeof(char));
#ifdef MEM_DEBUG
				//memdeb_add(buff);
#endif
				bool found = false;
				const unsigned max_depth = 50;
				unsigned depth = 0;
				while (depth < max_depth) {
					line = strtok_r(NULL, "\n", &line_sp);
					if (line == NULL)
						break;
					int shift = 0;
					while (isspace(*line)) {
						line++;
						shift++;
					}
					if (strncasecmp(line, "fend", 4) == 0) {
						found = true;
						break;
					}
					line -= shift;
					fwrite(line, sizeof(char), strlen(line), file);
					fprintf(file, "\n");
					depth++;
				}
				//free(buff);
				//buff = NULL;
				fflush(file);
				fclose(file);
				file = NULL;
				puts("Here");
				// Error checking
				if (!found) {
					fprintf(stderr,
							"Error while parsing template: templateFile: '%s' was not closed with a 'FEND'\n",
							filename);
					free(filename-fnShift);
					exit(1);
				}
				puts("HERE");
				free(filename-fnShift);
				filename = NULL;
				if (line == NULL) {
					fprintf(stderr, "");
				}
			}
			//printf("%s\n", symbol);
		}
	}
	free(buffer);
	free(array_last(dirs));
	array_pop(&dirs);
	array_destroy(&dirs);

	//printf("%s\n", ((File*)array_get(ret.children,2))->name);
	return ret;
}

File *file_create(const char *name, bool isFile, Array children) {
	File *ret = malloc(sizeof(File));
	*ret = (File){ "", isFile, children };
	strncpy(ret->name, name, 16);
	return ret;
}
