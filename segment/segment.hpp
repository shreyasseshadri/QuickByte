#pragma once

#include "../indexers/indexer.hpp"
#include "../file-storages/local-file-storage/local-file-storage.hpp"

#define SEGMENT_LIMIT 50
class Segment
{
public:
    // A link to the next Segment
    Segment *next;
    // A link to the previous Segment
    Segment* prev;

    Indexer *indexer;

    std::string fileName;
    LocalFileStorage fileStorage;

    long int segmentSizeLeft;
    
    Segment(Indexer* idxr,std::string name);
    void write_to_segment(std::string key,std::string value);
    std::pair<bool,std::string> read_from_segment(std::string key);
    bool delete_if_exists(std::string key);
};