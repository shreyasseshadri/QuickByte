#include <bits/stdc++.h>

#include "disk-storage.hpp"

#define DATA_FILE "data.txt"

DiskStorage::DiskStorage(IndexerType type)
{
    switch (type)
    {
    case MAP_INDEXER:
    {
        indexer = new MapIndexer();
        break;
    }
    default:
    {
        indexer = new MapIndexer();
        break;
    }
    }
}

DiskStorage::~DiskStorage() {}

void DiskStorage::upsert(std::string key, std::string value)
{
    if (indexer == NULL)
    {
        printf("Indexer not initialized");
        exit(-1);
    }
    long offset_at = fileStorage.writeValue(DATA_FILE, value);
    printf("Inserted at %ld\n", offset_at);

    indexer->index(key, value, offset_at, value.size());
}

std::pair<bool, std::string> DiskStorage::retrieve(std::string key)
{
    std::pair<long, long> index_data = indexer->retrieve(key);
    long offset = index_data.first;
    long size = index_data.second;

    if (offset == -1)
    {
        printf("No such key exists\n");
        return std::make_pair(false, "");
    }

    printf("Retrieving at %ld Offset of size %ld\n", offset, size);
    char *buffer = (char *)malloc(size);
    fileStorage.readAtOffset(DATA_FILE, offset, size, buffer);
    std::string value(buffer, size);
    free(buffer);
    printf("Value Retrieved: ");
    std::cout << value;
    std::cout << "\n";
    return std::make_pair(true, value);
}
