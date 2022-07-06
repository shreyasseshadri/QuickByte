#include "segment.hpp"

Segment::Segment(Indexer *idxr, std::string name)
{
    indexer = idxr;
    fileName = name;
    segmentSizeLeft = SEGMENT_LIMIT;
    next = NULL;
};

void Segment::write_to_segment(std::string key, std::string value)
{
    if (indexer == NULL)
    {
        printf("Indexer not initialized");
        exit(-1);
    }

    long offset_at = fileStorage.writeValue((char *)fileName.c_str(), value);
    printf("Inserted at %ld\n", offset_at);

    indexer->index(key, value, offset_at, value.size());
    segmentSizeLeft -= value.size();
    std::cout << "Segment Size Left: "
              << " " << segmentSizeLeft << "\n";
}

std::pair<bool, std::string> Segment::read_from_segment(std::string key)
{
    std::pair<long, long> index_data = indexer->retrieve(key);
    long offset = index_data.first;
    long size = index_data.second;

    if (offset == -1)
    {
        return std::make_pair(false, "");
    }

    printf("Retrieving at %ld Offset of size %ld\n", offset, size);
    char *buffer = (char *)malloc(size);
    fileStorage.readAtOffset((char *)fileName.c_str(), offset, size, buffer);
    std::string value(buffer, size);
    free(buffer);
    printf("Value Retrieved: ");
    std::cout << value;
    std::cout << "\n";

    return std::make_pair(true, value);
}

bool Segment::delete_if_exists(std::string key)
{
    std::pair<long, long> index_data = indexer->retrieve(key);

    // Key does not exist in this segment
    if (index_data.first == -1)
        return false;
    
    // Key exists, and is to be removed
    indexer->remove(key);
    return true;
}