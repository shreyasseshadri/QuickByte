test: test.c
	g++ -o test.out file/file.o utils/error.o test.o

test.c: file_api.h error_handler.h
	g++ -c test.c -o test.o

file_api.h:
	g++ -c file/file_api.h -o file/file.o

error_handler.h:
	g++ -c utils/error_handler.h -o utils/error.o

clean: clean_utils clean_file
	rm -f *.o
	rm -f *.gch
	rm -f *.out

clean_utils:
	rm -f utils/*.o utils/*.gch

clean_file:
	rm -f file/*.o file/*.gch