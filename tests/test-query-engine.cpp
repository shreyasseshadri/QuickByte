#include <bits/stdc++.h>

#include "../storage/storage.hpp"
#include "../query-engine/query-engine.hpp"

int main()
{
    Storage *storage_engine = Storage::factory(IN_MEMORY);

    QueryEngine *query_engine = new QueryEngine(storage_engine);

    QueryResponse *r1 = query_engine->process_and_execute("UPSERT FOO BAR");
    assert(r1->response_status == SUCCESS);
    assert(r1->message == "Value Inserted");

    r1 = query_engine->process_and_execute("GET FOO");
    assert(r1->response_status == SUCCESS);
    assert(r1->result.second == "BAR");

    r1 = query_engine->process_and_execute("UPSERT FOO BAR2");
    assert(r1->response_status == SUCCESS);
    assert(r1->message == "Value Updated");

    r1 = query_engine->process_and_execute("GET FOO");
    assert(r1->response_status == SUCCESS);
    assert(r1->result.second == "BAR2");

    r1 = query_engine->process_and_execute("DELETE FOO");
    assert(r1->response_status == SUCCESS);
    assert(r1->message == "Key Deleted");

    r1 = query_engine->process_and_execute("GET FOO");
    assert(r1->response_status == SUCCESS);
    assert(r1->result.first == false);

    r1 = query_engine->process_and_execute("UPSERT FOO");
    assert(r1->response_status == FAILURE);

    r1 = query_engine->process_and_execute("GET ");
    assert(r1->response_status == FAILURE);

    r1 = query_engine->process_and_execute("TYPE ");
    assert(r1->response_status == FAILURE);
}