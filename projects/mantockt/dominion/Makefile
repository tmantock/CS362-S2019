CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)


#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

assertion.o: assertion.h assertion.c
	gcc -c assertion.c -g $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o assertion.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o assertion.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o assertion.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o assertion.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o assertion.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o assertion.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o assertion.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o assertion.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o assertion.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o assertion.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o assertion.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o assertion.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o assertion.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o assertion.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o assertion.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o assertion.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c assertion.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c assertion.c -g dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c assertion.c -g dominion.o rngs.o $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	echo "######## Unit Test 1 #######" >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo "######## Unit Test 2 #######" >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo "######## Unit Test 3 #######" >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo "######## Unit Test 4 #######" >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo "######## Card Test 1 #######" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo "######## Card Test 2 #######" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo "######## Card Test 3 #######" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	echo "######## Card Test 4 #######" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestresults: randomtestcard1 randomtestcard2 randomtestadventurer
	rm -rf randomtestresults.out
	echo "######## Random Test 1 #######" >> randomtestresults.out
	./randomtestcard1 >> randomtestresults.out
	gcov -f -b dominion.c | python gcov_function_result.py steward_effect >> randomtestresults.out
	echo "######## Random Test 2 #######" >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	gcov -f -b dominion.c | python gcov_function_result.py smithy_effect >> randomtestresults.out
	echo "######## Random Test Adventurer #######" >> randomtestresults.out
	./randomtestadventurer >> randomtestresults.out
	gcov -f -b dominion.c | python gcov_function_result.py adventurer_effect >> randomtestresults.out

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -rf unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	rm -rf randomtestcard1 randomtestcard2 randomtestadventurer
