LOCAL_FILE_STORAGE=file-storage/local-file-storage
MAP_INDEXER=indexers/map-indexer

test: compile-test quick-byte
	g++ tests/test.o QuickByte.o -o test.out 

quick-byte: compile-storage-api link-indexers link-file-storages link-utils
# Link indexers storage-api file-storage and utilities into the final QuickByte object
	ld -relocatable indexers/indexer.o file-storage/file-storage.o storage/storage-api.o utils/utils.o -o QuickByte.o

compile-storage-api:
	g++ -c storage/storage-api.cpp -o storage/storage-api.o

link-indexers: compile-map-indexer # Later on multple indexers will be compiled
# For now there is only one type of indexer, so the linking process consists of only one object
	ld -relocatable ${MAP_INDEXER}/map-indexer.o -o indexers/indexer.o

link-file-storages: compile-file-storage # Later on multiple file storages will be compiled
# For now there is only one type of file storage, so the linking process consists of only one object
	ld -relocatable ${LOCAL_FILE_STORAGE}/local-file-storage.o -o file-storage/file-storage.o

compile-file-storage:
	g++ -c ${LOCAL_FILE_STORAGE}/local-file-storage.cpp -o ${LOCAL_FILE_STORAGE}/local-file-storage.o

compile-map-indexer:
	g++ -c ${MAP_INDEXER}/map-indexer.cpp -o ${MAP_INDEXER}/map-indexer.o

compile-test:
	g++ -c tests/test.cpp -o tests/test.o

link-utils: compile-error-handler
# For now there is only one utilty so only linking that
	ld -relocatable utils/error-handler/error-handler.o -o utils/utils.o

compile-error-handler:
	g++ -c utils/error-handler/error-handler.cpp -o utils/error-handler/error-handler.o

clean:
	find . -type f -name '*.o' -delete
	rm -f *.out

clear_data:
	rm -f data.txt