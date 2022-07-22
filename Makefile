LOCAL_FILE_STORAGE=file-storages/local-file-storage
MAP_INDEXER=indexers/map-indexer

test: compile-test quick-byte
	g++ -g -O0 -pthread tests/test.o QuickByte.o -o test.out 

compile-cli:
	g++ cli/cli.cpp -o cli/cli.o -L/usr/local/lib -I/usr/local/include -lreadline

server: compile-server quick-byte
	g++ -g -O0 -pthread server/server.o QuickByte.o -o server/server.out

compile-server:
	g++ -g -c -pthread server/server.cpp -o server/server.o

test-query-engine: compile-test-query quick-byte
	g++ -g -O0 -pthread tests/test-query.o QuickByte.o -o test.out 

compile-test-query: 
	g++ -g -c tests/test-query-engine.cpp -o tests/test-query.o

ci-test:
	chmod +x ./test.out
	./test.out

quick-byte: lib-folder compile-storage-api compile-indexers compile-file-storages compile-utils compile-segment compile-query-engine
# Link indexers storage-api file-storage and utilities into the final QuickByte object
	ld -relocatable lib/indexers/*.o lib/file-storages/*.o lib/utilities/*.o lib/engines/*.o lib/segment/*.o lib/query-engine/*.o -o QuickByte.o

compile-query-engine:
	g++ -g -c query-engine/query-engine.cpp -o lib/query-engine/query-engine.o

compile-disk-storage:
	# -g to include the symbol table in the output for debugging purposes
	g++ -g -c storage/disk-storage/disk-storage.cpp -o lib/engines/disk-storage.o

compile-in-memory-storage:
	g++ -g -c storage/in-memory-storage/in-memory-storage.cpp -o lib/engines/in-memory-storage.o

lib-folder:
	mkdir -p lib/indexers lib/file-storages lib/utilities lib/engines lib/segment lib/query-engine
	
compile-storage-api: compile-disk-storage compile-in-memory-storage
	g++ -g -c storage/storage.cpp -o lib/engines/storage.o

compile-indexers: compile-map-indexer

compile-file-storages: compile-local-file-storage

compile-utils: compile-error-handler compile-bst compile-segment-utils

compile-segment:
	g++ -g -c segment/segment.cpp -o lib/segment/segment.o

compile-local-file-storage:
	g++ -g -c ${LOCAL_FILE_STORAGE}/local-file-storage.cpp -o lib/file-storages/local-file-storage.o

compile-map-indexer:
	g++ -g -c ${MAP_INDEXER}/map-indexer.cpp -o lib/indexers/map-indexer.o

compile-test:
	g++ -g -c tests/test.cpp -o tests/test.o

compile-segment-utils:
	g++ -g -c utils/segment/segment.cpp -o lib/utilities/segment-utils.o

compile-error-handler:
	g++ -g -c utils/error-handler/error-handler.cpp -o lib/utilities/error-handler.o

compile-bst:
	g++ -g -c utils/bst/bst.cpp -o lib/utilities/bst.o

clean: clear_data
	find . -type f -name '*.o' -delete
	rm -f *.out
	rm -f -r lib

clear_data:	
	rm -f data.txt
	rm -f DATA_FILE*

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
