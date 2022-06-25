#include "storage.hpp"

#include "./in-memory-storage/in-memory-storage.hpp"
#include "./disk-storage/disk-storage.hpp"

Storage *Storage::factory(StorageType type = DISK)
{
    switch (type)
    {
    case DISK:
        return new DiskStorage(MAP_INDEXER);
    case IN_MEMORY:
        return new InMemoryStorage();
    default:
        return new DiskStorage(MAP_INDEXER);
    }
}
