#include <bits/stdc++.h>

#include "storage-api.hpp"
#include "../utils/segment/segment.hpp"

Storage::Storage(IndexerType type)
{
    indexerType = type;
    Indexer *idxr = instantiateIndexer(indexerType);
    Segment *segmentHead = new Segment(idxr, fileNamePrefix + "0");
    currentSegment = segmentHead;
    segmentCount = 1;
}

Indexer *Storage::instantiateIndexer(IndexerType type)
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

void Storage::insert(std::string key, std::string value)
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

std::pair<bool, std::string> Storage::retrieve(std::string key)
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
