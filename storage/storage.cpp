#include "storage.hpp"

#include "./in-memory-storage/in-memory-storage.hpp"
#include "./disk-storage/disk-storage.hpp"

Storage *Storage::factory(StorageType type = DISK, bool should_lock)
{
    switch (type)
    {
    case DISK:
        return new DiskStorage(MAP_INDEXER);
    case IN_MEMORY:
        return new InMemoryStorage(should_lock);
    default:
        return new DiskStorage(MAP_INDEXER);
    }
}
