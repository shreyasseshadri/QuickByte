#include <bits/stdc++.h>

#include "../storage/storage.hpp"

enum status
{
    SUCCESS,
    FAILURE
};

typedef struct QueryResponse
{
    status response_status;
    std::string message;
    std::pair<bool, std::string> result; // Empty if nothing is to be retrieved
};

class QueryEngine
{

public:
    QueryEngine(Storage *storage);

    QueryResponse *process_and_execute(std::string query);

private:
    std::string delimiter;
    Storage *storage_engine;

    std::pair<size_t, std::string> parse_key(std::string query, size_t pos);
    QueryResponse *make_response(status response_status, std::string response_message, std::pair<bool,std::string> result = std::make_pair(false, ""));
};