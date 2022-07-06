#pragma once

#include "../file-storage.hpp"

class LocalFileStorage : public FileStorage
{
private:
    char *delimiter = "\n";

public:
    /**
     * @brief writes value to a given local file
     * @param file_name File name
     * @param data the data
     * @return long the offset at which the value was written
     */
    long writeValue(char *file_name, std::string data);

    /**
     * @brief Read a local file at an offset
     * @param file_name File Name
     * @param offset The offset to read from
     * @param buff_size The buffer size
     * @param buffer Buffer to which data will be copied onto
     */
    void readAtOffset(char *file_name, int offset, size_t buff_size, char *buffer);
};