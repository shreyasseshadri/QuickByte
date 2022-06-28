#include <bits/stdc++.h>

#pragma once

enum StorageType
{
    DISK,
    IN_MEMORY
};

class Storage
{
private:
    Storage *storage_engine;

public:
    static Storage *factory(StorageType);

    virtual ~Storage(){};

    /**
     * @brief Insert a key value pair
     * @param key The key
     * @param value The value
     */
    virtual void upsert(std::string key, std::string value) = 0;

    /**
     * @brief Retrieve the value given the key
     * @param key The key
     * @return std::string Returns value or Empty String if not found
     */
    virtual std::pair<bool, std::string> retrieve(std::string key) = 0;
};