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
int addAdventurerCard(int, struct gameState *);
int countTreasureCards(int, struct gameState *);
int checkAdventurerEffect(int, struct gameState *);
void randomizeDeck(int player, struct gameState *state);
void ensureTreasureCardsPresentInDiscardDeck(int, int, struct gameState *);

int main(int argc, char const *argv[])
{
  runTest();
  return 0;
}

void runTest()
{
  int expect = 5, passes = 0, iterations = 2000;
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
    G.discardCount[p] = floor(Random() * 100);
    G.playedCardCount = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    // The deck needs to be have at least three cards in it, so there are three treasure
    // cards tp be drawn, or else the adventurer_effect function will never exit and there
    // will be a segmentation fault.
    if (G.discardCount[p] < 3)
    {
      G.discardCount[p] = 3;
    }
    if (G.deckCount[p] < 1)
    {
      G.deckCount[p] = 1;
    }
    // Make sure there are treasure cards in the deck for the adventurer while loop condition
    // to be satisfied.
    randomizeDeck(p, &G);
    ensureTreasureCardsPresentInDiscardDeck(3, p, &G);
    memset(G.hand[p], 0, sizeof(int) * G.handCount[p]);
    memset(G.playedCards, 0, sizeof(int) * G.playedCardCount);
    passes += checkAdventurerEffect(p, &G);
  }
  clock_t end = clock();

  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  double minutes = elapsed / 60.;
  int seconds = (int)elapsed % 60;

  fflush(stdout);
  dup2(stdo, STDOUT_FILENO);

  printf("%d Tests Ran with %d Assertions per Test\nPASS: %d\nFAIL: %d\nElapsed: %d min %d sec\n\n", iterations, expect, passes, (expect * iterations) - passes, (int)minutes, seconds);
}

void randomizeDeck(int player, struct gameState *state)
{
  for (int i = 0; i < state->deckCount[player]; i++)
  {
    state->deck[player][i] = (int)(Random() * 26);
  }
}

void ensureTreasureCardsPresentInDiscardDeck(int count, int player, struct gameState *state)
{
  // Evenly distribute the treasure cards throughout the array by finding the sections
  // of the array.
  int rate = floor(state->discardCount[player] / count);

  for (int i = 0; i < state->discardCount[player]; i += rate)
  {
    state->discard[player][i] = copper;
  }
}

int addAdventurerCard(int player, struct gameState *state)
{
  int i = 0;

  for (; i < state->handCount[player]; i++)
  {
    if (state->hand[player][i] == adventurer)
    {
      return i;
    }
  }

  state->hand[player][i] = adventurer;
  state->handCount[player]++;

  return i;
}

int countTreasureCards(int player, struct gameState *state)
{
  int treasure = 0;

  for (int i = 0; i < state->handCount[player]; i++)
  {
    int card = state->hand[player][i];

    if (card == copper || card == silver || card == gold)
    {
      treasure++;
    }
  }

  return treasure;
}

int checkAdventurerEffect(int player, struct gameState *state)
{
  int passes = 0;
  struct gameState copied;
  int handPos = addAdventurerCard(player, state);

  memcpy(&copied, state, sizeof(struct gameState));

  int r = adventurer_effect(player, state);
  int preTreasureCount = countTreasureCards(player, &copied);
  int newTreasureCount = countTreasureCards(player, state);

  passes += assert_that(equals(r, 0), "checkAdventurerEffect", "Correct return value for function call.");
  passes += assert_that(equals(state->playedCards[state->playedCardCount - 1], adventurer), "checkAdventurerEffect", "The Adventurer card was discarded.");
  passes += assert_that(equals(state->handCount[player], copied.handCount[player] + 3 - 1), "checkAdventurerEffect", "3 cards were drawn by the player.");
  passes += assert_that(equals(newTreasureCount, preTreasureCount + 3), "checkAdventurerEffect", "Three treasure cards were drawn.");
  passes += assert_that(not_equals(state->hand[player][handPos], adventurer), "checkAdventurerEffect", "Adventurer card was removed from the hand.");

  return passes;
}
