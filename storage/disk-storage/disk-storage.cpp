#include <bits/stdc++.h>

#include "disk-storage.hpp"

#define DATA_FILE "data.txt"
#include "../storage.hpp"
#include "../../utils/segment/segment.hpp"

DiskStorage::DiskStorage(IndexerType type)
{
    indexerType = type;
    Indexer *idxr = instantiateIndexer(indexerType);
    Segment *segmentHead = new Segment(idxr, fileNamePrefix + "0");
    currentSegment = segmentHead;
    segmentCount = 1;
}

Indexer *DiskStorage::instantiateIndexer(IndexerType type)
{
    Indexer *indexer = NULL;
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
    return indexer;
}

DiskStorage::~DiskStorage() {}

void DiskStorage::upsert(std::string key, std::string value)
{
    if (currentSegment->segmentSizeLeft < (long)value.size())
    {
        Indexer *idxr = instantiateIndexer(indexerType);
        Segment *newSegment = new Segment(idxr, fileNamePrefix + std::to_string(segmentCount));
        link_segments(currentSegment, newSegment);
        segmentCount += 1;
        currentSegment = newSegment;
    }

    currentSegment->writeToSegment(key, value);
}

std::pair<bool, std::string> DiskStorage::retrieve(std::string key)
{
    std::pair<bool, std::string> segmentInfo = std::make_pair(false, "");
    Segment *segmentPointer = currentSegment;

    while (segmentPointer && !segmentInfo.first)
    {
        segmentInfo = segmentPointer->readFromSegment(key);
        segmentPointer = segmentPointer->prev;
    }

    if (!segmentInfo.first)
    {
        std::cout << "Key: " << key << " does not exist\n";
    }

    return segmentInfo;
}
