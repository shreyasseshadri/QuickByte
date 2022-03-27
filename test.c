#include <stdio.h>
#include <stdlib.h>

#include "file_api.h"

int main()
{
	char *test = "This is a test value";
	write_value_to_file("data.txt", test);

	int buff_size = strlen(test);
	char *buffer = (char *)malloc(buff_size);
	read_from_file_at_offset("data.txt", 0, buff_size, buffer);
	printf("Data Read: %s",buffer);
	return 0;
}