#include <bits/stdc++.h>
#include <stdio.h>

#include "../indexer.hpp"

class MapIndexer : public Indexer
{
private:
    std::unordered_map<std::string, std::pair<long, long>> key_indexer;

public:
    void index(std::string key, std::string value, long int offset, long int size);

    std::pair<long, long> retrieve(std::string key);
};