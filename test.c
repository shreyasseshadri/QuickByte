#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

#include "storage/storage-api.h"

int main()
{
	std::string test1 = "this is test1";
	std::string test2 = "this is test2";

	key_insert("key1", test1);
	std::string data = key_retrieve("key1");

	key_insert("key2", test2);
	std::string data2 = key_retrieve("key2");
	
	std::string data3 = key_retrieve("key3");
	return 0;
}