#include "assertion.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "time.h"
#include <fcntl.h>
#include <unistd.h>

void runTest();
int addStewardCard(int, struct gameState *);
int checkStewardEffect(int, struct gameState *);

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

  int std = dup(STDOUT_FILENO);
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
    // Make sure there are at least three cards in the player's hand in case the choice to
    // discard cards have been selected.
    if (G.handCount[p] < 2)
    {
      G.handCount[p] = 2;
    }

    memset(G.deck[p], 0, sizeof(int) * G.deckCount[p]);
    memset(G.hand[p], 0, sizeof(int) * G.handCount[p]);
    memset(G.playedCards, 0, sizeof(int) * G.playedCardCount);
    memset(G.discard[p], 0, sizeof(int) * G.discardCount[p]);
    passes += checkStewardEffect(p, &G);
  }
  clock_t end = clock();

  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  double minutes = elapsed / 60.;
  int seconds = (int)elapsed % 60;

  fflush(stdout);
  dup2(std, STDOUT_FILENO);

  printf("%d Tests Ran with %d Assertions per Test\nPASS: %d\nFAIL: %d\nElapsed: %d min %d sec\n\n", iterations, expect, passes, (expect * iterations) - passes, (int)minutes, seconds);
}

int addStewardCard(int player, struct gameState *state)
{
  int i = 0;

  for (; i < state->handCount[player]; i++)
  {
    if (state->hand[player][i] == steward)
    {
      return i;
    }
  }

  state->hand[player][i] = steward;
  state->handCount[player]++;

  return i;
}

int checkStewardEffect(int player, struct gameState *state)
{
  int passes = 0;
  struct gameState copied;
  int handPos = addStewardCard(player, state);

  memcpy(&copied, state, sizeof(struct gameState));
  int choice = (Random() * 3) + 1,
      discardCard1 = handPos != 0 ? 0 : 1,
      discardCard2 = handPos != 2 ? 2 : 3;
  int r = steward_effect(player, handPos, choice, discardCard1, discardCard2, state);

  passes += assert_that(equals(r, 0), "checkStewardEffect", "Correct return value for function call.");
  passes += assert_that(not_equals(state->hand[player][handPos], steward), "checkStewardEffect", "Steward card was removed from hand.");
  passes += assert_that(equals(state->playedCards[state->playedCardCount - 1], steward), "checkStewardEffect", "The Steward card was discarded.");

  if (choice == 1)
  {
    passes += assert_that(equals(state->handCount[player], copied.handCount[player] + 2 - 1), "checkStewardEffect", "Two cards were drawn to the player's hand");
    passes += assert_that(equals(state->coins, copied.coins), "checkStewardEffect", "The coins are unchanged.");
  }
  else if (choice == 2)
  {
    passes += assert_that(equals(state->coins, copied.coins + 2), "checkStewardEffect", "The coins amount was increased by 2.");
    passes += assert_that(equals(state->handCount[player], copied.handCount[player] - 1), "checkStewardEffect", "No cards were added or removed besides the played Steward card.");
  }
  else
  {
    passes += assert_that(equals(state->coins, copied.coins), "checkStewardEffect", "The coins are unchanged.");
    passes += assert_that(equals(state->handCount[player], copied.handCount[player] - 2 - 1), "checkStewardEffect", "Two cards were removed to the player's hand");
  }

  return passes;
}