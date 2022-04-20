#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../src/storage-api.cpp"

int main()
{

	Storage storage(MAP_INDEXER);

	std::string value = "This is Value1";
	storage.insert("key1", value);
	std::string valueRetrieved = storage.retrieve("key1");
	assert(value == valueRetrieved);

	std::string value2 = "This is Value2";
	storage.insert("key2", value2);
	std::string valueRetrieved2 = storage.retrieve("key2");
	assert(value2 == valueRetrieved2);

	return 0;
}