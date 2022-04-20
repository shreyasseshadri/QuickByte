#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

#include "../include/indexer.hpp"

class MapIndexer : public Indexer
{
private:
    std::unordered_map<std::string, std::pair<long, long>> key_indexer;

public:
    void index(std::string key, std::string value, long int offset, long int size)
    {
        key_indexer[key] = std::make_pair(offset, size);
    }

    std::pair<long, long> retrieve(std::string key)
    {
        long error = -1;
        return (key_indexer.find(key) != key_indexer.end())
                   ? key_indexer[key]
                   : std::make_pair(error, error);
    }
};