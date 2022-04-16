#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

#include "../file/file_api.h"
#include "../indexer/map-indexer.h" /* Have to make it a generic class */

void key_insert(std::string key, std::string value);
std::string key_retrieve(std::string key);

#define DATA_FILE "data.txt"

void key_insert(std::string key, std::string value)
{
    long offset_at = write_value_to_file(DATA_FILE, value);
    printf("Inserted at %ld\n", offset_at);
    index_key(key, offset_at, value.size());
}

std::string key_retrieve(std::string key)
{
    std::pair<long, long> index_data = retrieve_index(key);
    long offset = index_data.first;
    long size = index_data.second;

    if (offset == -1)
    {
        printf("No such key exists");
        return "";
    }

    printf("Retrieving at %ld Offset of size %ld\n", offset, size);
    char *buffer = (char *)malloc(size+1);
    read_from_file_at_offset(DATA_FILE, offset, size, buffer);
    printf("Value Retrieved: %s\n", buffer);
    std::string value(buffer,size+1); /* There is some issue in conversion of char array to string*/
    return value;
}