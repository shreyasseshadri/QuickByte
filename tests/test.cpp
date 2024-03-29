#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <threads.h>

#include "../storage/storage.hpp"
#include <time.h>

void test_engine_concurrency(Storage *storage, int id)
{
	std::string key = std::to_string(id);
	storage->upsert(key, key);
	assert(storage->retrieve(key).second == key);
	storage->delete_key(key);
	assert(storage->retrieve(key).first == false);
}

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

double testing_concurrency()
{
	Storage *in_memory_storage = Storage::factory(IN_MEMORY, true);
	int n = 10000;
	std::thread mythreads[n];
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	for (int i = 0; i < n; i++)
	{
		mythreads[i] = std::thread(test_engine_concurrency, in_memory_storage, i);
	}

	for (int i = 0; i < n; i++)
	{
		mythreads[i].join();
	}
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	delete in_memory_storage;
	return cpu_time_used;
}

int main()
{
	long double time_taken = 0;
	int n_times = 100;
	for (int i = 0; i < n_times; i++)
	{
		time_taken += testing_concurrency();
	}


	printf("%f",(double)time_taken/n_times);
}