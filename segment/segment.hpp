#pragma once

#include "../indexers/indexer.hpp"
#include "../file-storages/local-file-storage/local-file-storage.hpp"

#define SEGMENT_LIMIT 20
class Segment
{
public:
    Segment *next;
    Segment* prev;

    Indexer *indexer;

    std::string fileName;
    LocalFileStorage fileStorage;

    long int segmentSizeLeft;
    
    Segment(Indexer* idxr,std::string name);
    void writeToSegment(std::string key,std::string value);
    std::pair<bool,std::string> readFromSegment(std::string key);
};