#include "query-engine.hpp"

QueryEngine::QueryEngine(Storage *storage)
{
    storage_engine = storage;
    delimiter = " "; // For now delimter is a simple space
}

QueryResponse *QueryEngine::make_response(status response_status, std::string response_message, std::pair<bool, std::string> result)
{
    QueryResponse *response = new QueryResponse();

    response->response_status = response_status;
    response->message = response_message;
    response->result = result;

    std::cout << response_message << "\n";

    return response;
}

std::pair<size_t, std::string> QueryEngine::parse_key(std::string query, size_t pos)
{
    size_t pos_end_key = query.find(delimiter, pos);

    if (pos_end_key == std::string::npos)
    {
        return std::make_pair(pos_end_key, "");
    }

    return std::make_pair(pos_end_key, query.substr(pos, pos_end_key - pos));
}

QueryResponse *QueryEngine::process_and_execute(std::string query)
{
    size_t pos = query.find(delimiter);

    if (pos == std::string::npos)
    {
        return make_response(FAILURE, "Unable to parse query");
    }

    std::string query_type = query.substr(0, pos);
    std::cout << "\nQuery: " << query << "\n";
    std::cout << "Query type: " << query_type << " pos: " << pos << "\n";

    if (query_type == "upsert")
    {
        std::pair<size_t, std::string> parse_result = parse_key(query, pos + delimiter.size());

        if (parse_result.first == std::string::npos)
        {
            return make_response(FAILURE, "Invalid query, no key found");
        }

        std::string key = parse_result.second;

        if (parse_result.first >= query.size() - 1)
        {
            return make_response(FAILURE, "Invalid query, no value found");
        }
        std::string value = query.substr(parse_result.first + delimiter.size());

        std::cout << "key " << key << "\n";
        std::cout << "value " << value << "\n";

        UPSERT response = storage_engine->upsert(key, value); // TODO: handling crashes

        return make_response(SUCCESS, response == INSERT ? "Value Inserted" : "Value Updated");
    }
    else if (query_type == "get")
    {

        if (pos + delimiter.size() >= query.size())
        {
            return make_response(FAILURE, "Invalid query, no key found");
        }

        std::string key = query.substr(pos + delimiter.size());
        std::cout << "Key " << key << "\n";

        std::pair<bool, std::string> result = storage_engine->retrieve(key);
        std::cout << result.second << " " << result.first << "\n";
        return make_response(SUCCESS, result.first? "Key retrieved": "Key Not found", result);
    }
    else if (query_type == "delete")
    {

        if (pos + delimiter.size() >= query.size())
        {
            return make_response(FAILURE, "Invalid query, no key found");
        }

        std::string key = query.substr(pos + delimiter.size());
        std::cout << "Key " << key << "\n";

        bool result = storage_engine->delete_key(key);

        return make_response(SUCCESS, result ? "Key Deleted" : "Key not found, not deleted");
    }
    else
    {
        return make_response(FAILURE, "Invalid Query Type");
    }
}