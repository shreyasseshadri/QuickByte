#include <bits/stdc++.h>
#include <stdio.h>

/**
 * @brief An abstract class of an indexer.
 * Any indexer must extend this class and implement the indexer functions 
 */
class Indexer
{
    public:
        /**
         * @brief Any indexer will be given the below four arguments to index, by the Storage API.
         * It may choose to index it however it wishes. For example an indexer can only use key,
         * offset, and size information and choose to ignore the value.
         * @param key The key
         * @param value The value
         * @param offset The offset of the file for which it was written
         * @param size The size of the value to be written
         */
        virtual void index(std::string key, std::string value, long int offset,long int size) = 0;

        /**
         * @brief An indexer must be able to retrieve the offset at which the file was written,
         * and the size of the value 
         * @param key 
         * @return std::pair<long, long> A pair of offset and size of value to read
         */
        virtual std::pair<long, long> retrieveKey(std::string key) = 0;
};