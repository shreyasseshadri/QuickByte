#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

#include "map-indexer.hpp"

void MapIndexer::index(std::string key, std::string value, long int offset, long int size)
{
    key_indexer[key] = std::make_pair(offset, size);
}

std::pair<long, long> MapIndexer::retrieve(std::string key)
{
    long error = -1;
    return (key_indexer.find(key) != key_indexer.end())
               ? key_indexer[key]
               : std::make_pair(error, error);
}