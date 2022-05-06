#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

#include "../file-storages/local-file-storage/local-file-storage.hpp"
#include "../indexers/indexer.hpp"
#include "../indexers/map-indexer/map-indexer.hpp"
#include "../segment/segment.hpp"

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
    Segment* currentSegment;
    long int segmentCount;
    std::string fileNamePrefix = "DATA_FILE_";
    IndexerType indexerType;

public:
    /**
     * @brief Construct a new Storage object by giving the indexer type
     * @param type Indexer type part of `IndexerType` Enum
     */
    Storage(IndexerType type);

    /**
     * @brief Insert a key value pair
     * @param key The key
     * @param value The value
     */
    void insert(std::string key, std::string value);

    /**
     * @brief Retrieve the value given the key
     * @param key The key
     * @return std::pair<bool,std::string> Returns a pair where first element returns if the key was found
     *  the second element contains the value if found or an empty string
     */
    std::pair<bool,std::string>  retrieve(std::string key);

    Indexer* instantiateIndexer(IndexerType type);
};