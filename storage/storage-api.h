#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

#include "../file/file_api.h"
#include "../indexer/map-indexer.h"

#define DATA_FILE "data.txt"

enum IndexerType
{
    MAP_INDEXER
};

/**
 * @brief This is the storage Engine API
 */
class Storage
{
private:
    Indexer *indexer = NULL;
    FileStorage fileStorage;

public:
    Storage(IndexerType type)
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

    void insert(std::string key, std::string value)
    {
        if (indexer == NULL)
        {
            printf("Indexer not initialized");
            exit(-1);
        }
        long offset_at = fileStorage.write_value_to_file(DATA_FILE, value);
        printf("Inserted at %ld\n", offset_at);

        indexer->index(key, value, offset_at, value.size());
    }

    std::string retrieve(std::string key)
    {
        std::pair<long, long> index_data = indexer->retrieveKey(key);
        long offset = index_data.first;
        long size = index_data.second;

        if (offset == -1)
        {
            printf("No such key exists\n");
            return "";
        }

        printf("Retrieving at %ld Offset of size %ld\n", offset, size);
        char *buffer = (char *)malloc(size);
        fileStorage.read_from_file_at_offset(DATA_FILE, offset, size, buffer);
        std::string value(buffer, size); /* There is some issue in conversion of char array to string*/

        printf("Value Retrieved: ");
        std::cout << value;
        std::cout << "\n";
        return value;
    }
};