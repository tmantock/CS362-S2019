#include "dominion.h"
#include "assertion.h"

void testSmithyEffect();
int addSmithyCard(int, struct gameState *);

int main()
{
  testSmithyEffect();
}

void testSmithyEffect()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 30, &G);

  int bonus = 0;
  int smithyCardPos = addSmithyCard(0, &G);
  int numberOfCards = G.handCount[0];

  cardEffect(smithy, 0, 0, 0, &G, smithyCardPos, &bonus);

  assert_that(equals(G.handCount[0], numberOfCards + 3 - 1), "testSmithyEffect", "Three cards have been added to player one's hand and the Smity card has been removed");
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