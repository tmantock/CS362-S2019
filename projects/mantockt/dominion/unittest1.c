#include "dominion.h"
#include "assertion.h"

void testSeaHagEffect();
int addSeaHagCard(int, struct gameState *);

int main()
{
  testSeaHagEffect();
}

void testSeaHagEffect()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 30, &G);

  addSeaHagCard(0, &G);
  int playerTwoDeckCount = G.deckCount[1];

  sea_hag_effect(0, &G);

  assert_that(equals(G.deckCount[1], playerTwoDeckCount - 1), "testSeaHagEffect", "The top card from the second player's deck was removed.");
  assert_that(equals(G.deck[1][G.deckCount[1] - 1], curse), "testSeaHagEffect", "The new top card of the deck is a curse card.");
}

int addSeaHagCard(int player, struct gameState *state)
{
  int i = 0;

  for (; i < state->handCount[player]; i++)
  {
    if (state->hand[player][i] == sea_hag)
    {
      return i;
    }
  }

  state->hand[player][i] = sea_hag;
  state->handCount[player]++;

  return i;
}
