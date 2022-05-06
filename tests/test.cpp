#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../storage/storage-api.hpp"

int main()
{

	Storage storage(MAP_INDEXER);

	std::string value = "This is Value1";
	storage.insert("key1", value);
	std::pair<bool,std::string> result = storage.retrieve("key1");
	assert(value == result.second);

	std::string value2 = "This is Value2";
	storage.insert("key2", value2);
	std::pair<bool,std::string> result1 = storage.retrieve("key2");
	assert(value2 == result1.second);

	storage.insert("key5", "This is value 5");

	std::cout << storage.retrieve("key5").first << "\n";

	storage.insert("key6", "This is value 6");

	std::cout << storage.retrieve("key6").first << "\n";

	storage.insert("key7", "This is value 7");

	std::cout << storage.retrieve("key7").first << "\n";

	storage.insert("key8", "This is value 8");

	std::cout << storage.retrieve("key8").first << "\n";

	storage.insert("key9", "This is value 9");

	std::cout << storage.retrieve("key10").first << "\n";

	return 0;
}