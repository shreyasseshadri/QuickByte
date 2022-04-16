#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

std::unordered_map<std::string, std::pair<long, long>> key_indexer;

void index_key(std::string key, long offset, long size);
std::pair<long, long> retrieve_index(std::string key);

void index_key(std::string key, long offset, long size)
{
    key_indexer[key] = std::make_pair(offset, size);
}

std::pair<long, long> retrieve_index(std::string key)
{
    long error = -1;
    return (key_indexer.find(key) != key_indexer.end()) ? key_indexer[key] : std::make_pair(error, error);
}