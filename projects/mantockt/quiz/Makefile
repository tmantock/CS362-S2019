CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

runtest: testme
	-./testme
	gcov -b testme.c >> results.out
	cat results.out

clean:
	rm -rf testme *.gcov *.gcda *.gcno *.out