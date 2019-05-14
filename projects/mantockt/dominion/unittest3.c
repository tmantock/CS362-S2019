#include "dominion.h"
#include "assertion.h"

void testSmithyDraw();
int addSmithyCard(int, struct gameState *);

int main()
{
  testSmithyDraw();
}

void testSmithyDraw()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 30, &G);
  int smithyCardPos = addSmithyCard(0, &G);

  int deckCount = G.deckCount[0];

  smithy_effect(0, smithyCardPos, &G);

  assert_that(equals(G.deckCount[0], deckCount - 3), "testSmithyDraw", "The three cards drawn are from the player's deck.");
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