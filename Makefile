LOCAL_FILE_STORAGE=file-storages/local-file-storage
MAP_INDEXER=indexers/map-indexer

test: compile-test quick-byte
	g++ tests/test.o QuickByte.o -o test.out 

ci-test:
	chmod +x ./test.out
	./test.out

quick-byte: lib-folder compile-storage-api compile-indexers compile-file-storages compile-utils
# Link indexers storage-api file-storage and utilities into the final QuickByte object
	ld -relocatable lib/indexers/*.o lib/file-storages/*.o lib/utilities/*.o lib/engines/*.o -o QuickByte.o

compile-disk-storage:
	g++ -c storage/disk-storage/disk-storage.cpp -o lib/engines/disk-storage.o

compile-in-memory-storage:
	g++ -c storage/in-memory-storage/in-memory-storage.cpp -o lib/engines/in-memory-storage.o

lib-folder:
	mkdir -p lib/indexers lib/file-storages lib/utilities lib/engines
	
compile-storage-api: compile-disk-storage compile-in-memory-storage
	g++ -c storage/storage.cpp -o lib/engines/storage.o

compile-indexers: compile-map-indexer

compile-file-storages: compile-local-file-storage

compile-utils: compile-error-handler compile-bst

compile-local-file-storage:
	g++ -c ${LOCAL_FILE_STORAGE}/local-file-storage.cpp -o lib/file-storages/local-file-storage.o

compile-map-indexer:
	g++ -c ${MAP_INDEXER}/map-indexer.cpp -o lib/indexers/map-indexer.o

compile-test:
	g++ -c tests/test.cpp -o tests/test.o

compile-error-handler:
	g++ -c utils/error-handler/error-handler.cpp -o lib/utilities/error-handler.o

compile-bst:
	g++ -c utils/bst/bst.cpp -o lib/utilities/bst.o

clean:
	find . -type f -name '*.o' -delete
	rm -f *.out
	rm -r lib

clear_data:
	rm -f data.txt

# Have kept it just in case, but will not be linking all together as they are independent
link-indexers: compile-map-indexer # Later on multple indexers will be compiled
# For now there is only one type of indexer, so the linking process consists of only one object
	ld -relocatable ${MAP_INDEXER}/map-indexer.o -o indexers/indexer.o

link-file-storages: compile-file-storage # Later on multiple file storages will be compiled
# For now there is only one type of file storage, so the linking process consists of only one object
	ld -relocatable ${LOCAL_FILE_STORAGE}/local-file-storage.o -o file-storages/file-storage.o

link-utils: compile-error-handler
# For now there is only one utilty so only linking that
	ld -relocatable utils/error-handler/error-handler.o -o utils/utils.o
