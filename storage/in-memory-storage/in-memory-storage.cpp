#include "./in-memory-storage.hpp"

InMemoryStorage::InMemoryStorage(bool should_lock)
{
    bst = new Bst(should_lock);
}

InMemoryStorage::~InMemoryStorage()
{
    delete bst;
}

void InMemoryStorage::upsert(std::string key, std::string value)
{
    bst->upsert_node(key, value);
}

std::pair<bool, std::string> InMemoryStorage::retrieve(std::string key)
{
    return bst->find_node(key);
}

bool InMemoryStorage::delete_key(std::string key)
{
    return bst->delete_node(key);
}