#include "assertion.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

void runTest();
int addSmithyCard(int, struct gameState *);
int checkSmithyEffect(int, struct gameState *);

int main(int argc, char const *argv[])
{
  runTest();
  return 0;
}

void runTest()
{
  int expect = 4, passes = 0, iterations = 2000;
  struct gameState G;

  SelectStream(2);
  PutSeed(3);

  int stdo = dup(STDOUT_FILENO);
  int devNull = open("/dev/null", O_WRONLY);
  dup2(devNull, STDOUT_FILENO);

  clock_t start = clock();
  for (int n = 0; n < iterations; n++)
  {
    for (int i = 0; i < sizeof(struct gameState); i++)
    {
      ((char *)&G)[i] = floor(Random() * 256);
    }

    int p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.playedCardCount = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);

    memset(G.deck[p], 0, sizeof(int) * G.deckCount[p]);
    memset(G.hand[p], 0, sizeof(int) * G.handCount[p]);
    memset(G.playedCards, 0, sizeof(int) * G.playedCardCount);
    memset(G.discard[p], 0, sizeof(int) * G.discardCount[p]);
    passes += checkSmithyEffect(p, &G);
  }
  clock_t end = clock();

  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  double minutes = elapsed / 60.;
  int seconds = (int)elapsed % 60;

  fflush(stdout);
  dup2(stdo, STDOUT_FILENO);

  printf("%d Tests Ran with %d Assertions per Test\nPASS: %d\nFAIL: %d\nElapsed: %d min %d sec\n\n", iterations, expect, passes, (expect * iterations) - passes, (int)minutes, seconds);
}

int addSmithyCard(int player, struct gameState *state)
{
  int i = 0;

  for (; i < state->handCount[player]; i++)
  {
    if (state->hand[player][i] == smithy)
    {
      return i;
    }
  }

  state->hand[player][i] = smithy;
  state->handCount[player]++;

  return i;
}

int checkSmithyEffect(int player, struct gameState *state)
{
  int passes = 0;
  struct gameState copied;
  int handPos = addSmithyCard(player, state);

  memcpy(&copied, state, sizeof(struct gameState));
  int r = smithy_effect(player, handPos, state);

  passes += assert_that(equals(r, 0), "checkSmithyEffect", "Correct return value for function call.");
  passes += assert_that(equals(state->playedCards[state->playedCardCount - 1], smithy), "checkSmithyEffect", "The Smithy card was discarded.");
  passes += assert_that(equals(state->handCount[player], copied.handCount[player] + 3 - 1), "checkSmithyEffect", "3 cards were drawn by the player.");
  passes += assert_that(not_equals(state->hand[player][handPos], smithy), "checkSmithyEffect", "Smithy card was removed from the hand.");

  return passes;
}
