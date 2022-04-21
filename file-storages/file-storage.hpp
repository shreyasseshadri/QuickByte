
#include <bits/stdc++.h>
#include "../utils/error-handler/error-handler.hpp"

/**
 * @brief This Class implements APIs for read and writes into a file.
 * This has been kept as an abstract class as a file read and write can also be over a network
 */
class FileStorage
{

public:
    /**
     * @brief writes value to the given file
     * @param file_name File name
     * @param data the data
     * @return long the offset at which the value was written
     */
    long writeValue(char *file_name, std::string data);

    /**
     * @brief Read from a file at an offset
     * @param file_name File Name
     * @param offset The offset to read from
     * @param buff_size The buffer size
     * @param buffer Buffer to which data will be copied onto
     */
    void readAtOffset(char *file_name, int offset, size_t buff_size, char *buffer);
};
