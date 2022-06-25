#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

#include "../../file-storages/local-file-storage/local-file-storage.hpp"
#include "../../indexers/indexer.hpp"
#include "../../indexers/map-indexer/map-indexer.hpp"
#include "../storage.hpp"

#define DATA_FILE "data.txt"

enum IndexerType
{
    MAP_INDEXER
};

/**
 * @brief This is the disk storage Engine API
 */
class DiskStorage : public Storage
{
private:
    Indexer *indexer = NULL;
    LocalFileStorage fileStorage;

public:
    /**
     * @brief Construct a new Storage object by giving the indexer type
     * @param type Indexer type part of `IndexerType` Enum
     */
    DiskStorage(IndexerType type);

    /**
     * @brief Insert a key value pair
     * @param key The key
     * @param value The value
     */
    void upsert(std::string key, std::string value);

    /**
     * @brief Retrieve the value given the key
     * @param key The key
     * @return std::string Returns value or Empty String if not found 
     */
    std::pair<bool,std::string> retrieve(std::string key);
};