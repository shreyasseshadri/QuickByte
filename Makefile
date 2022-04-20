test: test_c
	g++ -o test.out test.o

test_c:
	g++ -c tests/test.cpp -o test.o

clean:
	rm -f *.o
	rm -f *.gch
	rm -f *.out

clear_data:
	rm -f data.txt