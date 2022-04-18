test: test_c
	g++ -o test.out test.o

test_c:
	g++ -c test.cpp -o test.o

clean: clean_utils clean_file
	rm -f *.o
	rm -f *.gch
	rm -f *.out

clean_utils:
	rm -f utils/*.o utils/*.gch

clean_file:
	rm -f file/*.o file/*.gch

clear_data:
	rm -f data.txt