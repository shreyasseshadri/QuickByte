#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../storage/storage.hpp"

void test_engine(Storage *storage)
{
	std::string value = "This is Value1";
	storage->upsert("key1", value);

	std::string valueRetrieved = storage->retrieve("key1").second;
	assert(value == valueRetrieved);

	std::string value2 = "This is Value2";
	storage->upsert("key2", value2);

	std::string valueRetrieved2 = storage->retrieve("key2").second;
	assert(value2 == valueRetrieved2);

	storage->upsert("key1", "Updated value 1");
	assert(storage->retrieve("key1").second == "Updated value 1");

	assert(storage->retrieve("Non existent").first == false);

	storage->delete_key("key2");
	assert(storage->retrieve("key2").first == false);
}

int main()
{
	Storage *disk_storage = Storage::factory(DISK);
	// Storage *in_memory_storage = Storage::factory(IN_MEMORY);

	test_engine(disk_storage);

	// test_engine(in_memory_storage);
	// delete in_memory_storage;
	return 0;
}