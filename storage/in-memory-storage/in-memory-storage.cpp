#include "./in-memory-storage.hpp"

InMemoryStorage::InMemoryStorage()
{
    printf("Here bst");
    bst = new Bst();
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