#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "../../utils/error-handler/error-handler.hpp"

#include "local-file-storage.hpp"

long LocalFileStorage::writeValue(char *file_name, std::string data)
{
	const char *buffer = data.c_str();
	char *write_data = (char *)malloc(strlen(buffer) + strlen(delimiter));

	strcpy(write_data, buffer);
	strcat(write_data, delimiter);

	size_t buffer_size = strlen(write_data);
	printf("Size of data %d \n", buffer_size);
	FILE *fp = fopen(file_name, "a");
	if (fp == NULL)
		exit(-1);

	long curr_offset = ftell(fp);

	fwrite(write_data, buffer_size, 1, fp);
	free(write_data);
	fclose(fp);
	return curr_offset;
}


void LocalFileStorage::readAtOffset(char *file_name, int offset, size_t buff_size, char *buffer)
{
	FILE *fp = fopen(file_name, "r");
	error_handler("Opening File");
	fseek(fp, offset, SEEK_SET); // Move file offset to specified offset
	error_handler("moving offset");

	fread(buffer, buff_size, 1, fp);
	error_handler("reading bytes");

	fclose(fp);
}
