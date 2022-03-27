#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "utils/error_handler.h"

void write_value_to_file(char *file_name, char *data);
void read_from_file_at_offset(char *file_name, int offset, size_t buff_size, char *buffer);

char *delimiter = "\n";

void write_value_to_file(char *file_name, char *data)
{
	char *write_data = (char *)malloc(strlen(data) + strlen(delimiter));

	strcpy(write_data, data);
	strcat(write_data, delimiter);

	size_t buffer_size = strlen(write_data);
	printf("Size of data %d \n", buffer_size);
	FILE *fp = fopen(file_name, "w+");
	if (fp == NULL)
		exit(-1);

	fwrite(write_data, buffer_size, 1, fp);
	free(write_data);
	fclose(fp);
}

void read_from_file_at_offset(char *file_name, int offset, size_t buff_size, char *buffer)
{
	FILE *fp = fopen(file_name, "r+");
	if (fp == NULL)
		exit(-1);

	off_t offset_set = fseek(fp, offset, SEEK_SET);
	error_handler("moving offset");
	printf("Offset moved to %d\n",offset_set);

	fread(buffer, buff_size,1,fp);
	error_handler("reading bytes");

	fclose(fp);
}
