#include "template.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

Template loadTemplate(const char *name) {
	char *path = malloc(10+strnlen(name, 16)+7+1);
	sprintf(path, "%s%s%s", "templates/", name, ".genert");
	FILE *file = fopen(path,"r");
	if(!file) {
		fprintf(stderr, "Couldn't open file: %s, %s\n", path, strerror(errno));
		exit(1);
	}
	char *buffer = NULL;
	long length = 0;
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	buffer = malloc(length);
	if(!buffer) {
		fprintf(stderr, "Couldn't allocate memory for buffer while loading template, %s\n", strerror(errno));
		exit(1);
	}
	fread(buffer, 1, length, file);
	fclose(file);
	//printf("%s\n", buffer);
	Template ret = { "", (File){ "", false, array_create(10) }};
	strncpy(ret.dir.name, path, 16);
	char *symbol_sp;
	Array dirs = array_create(10);
	char *line_sp;
	for(
	char *line = strtok_r(buffer, "\n", &line_sp); 
	line != NULL; 
	line = strtok_r(NULL, "\n", &line_sp)) {

	for(
	char *symbol = strtok_r(line, " \t", &symbol_sp); 
	symbol != NULL; 
	symbol = strtok_r(NULL, " \t", &symbol_sp)) {
		if(strncasecmp(symbol, "template", 8) == 0){
			strncpy(ret.name, strtok_r(NULL, " \t", &symbol_sp), 16);
		} else if(strncasecmp(symbol, "dir", 3) == 0) {
			array_add(&dirs, 
			(void*)(file_create(strtok_r(NULL, " \t", &symbol_sp), false, array_create(2))));
			//printf("here %s\n", symbol);
		} else if(strncasecmp(symbol, "dend", 3) == 0) {
			free(dirs.array[dirs.used]);
			array_pop(&dirs);
		} else if(strncasecmp(symbol, "file", 4) == 0) {
			char *filename = strtok_r(NULL, " \t", &symbol_sp);
			char *buff = malloc(512);
			bool found = false;
			while(true) {
				line = strtok_r(NULL, "\n", &line_sp);
				if(line == NULL)
					break;
				while(isspace(*line))
						line++;
				if(strncasecmp(line, "fend", 4) == 0)
					break;
				strcat(buff, line);
				strncat(buff, "\n", 1);
			}
			printf("%s\n", buff);
			free(buff);
			if(line == NULL) {
				fprintf(stderr,
				"%d Error while parsing template: file: '%s' was not closed with a 'FEND'\n", found, filename);
				exit(1);
			}
			puts("\n\n");
		}
		//printf("%s\n", symbol);
	}
	}
	printf("%s\n", ((File*)array_get(ret.dir.children,2))->name);
	free(path);
	free(buffer);
	array_destroy(&ret.dir.children);
	for(int i = 0;i < dirs.used; i++) 
		free(array_get(dirs,i));
	array_destroy(&dirs);
	return ret;
}

File *file_create(const char *name, bool isFile, Array children) {
	File *ret = malloc(sizeof(File));
	*ret = (File){ "", isFile, children };
	strncpy(ret->name, name, 16);
	return ret;
}
