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
	FILE *fp = fopen(file_name, "a+");
	if (fp == NULL)
		exit(-1);

	fwrite(write_data, buffer_size, 1, fp);
	free(write_data);
	fclose(fp);
}

void read_from_file_at_offset(char *file_name, int offset, size_t buff_size, char *buffer)
{
	FILE *fp = open("data.txt", "a+");
	if (fp == NULL)
		exit(-1);

	off_t offset_set = lseek(fp, offset, SEEK_SET);
	if (offset_set < 0)
		error_handler("moving offset");

	ssize_t bytes_read = read(fp, buffer, buff_size);

	if (bytes_read != buff_size)
		error_handler("reading bytes");

	buffer[bytes_read] = 0x00; /* Setting the EOC */
	fclose(fp);
}
