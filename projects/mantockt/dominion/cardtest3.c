#include "dominion.h"
#include "assertion.h"

void testGreatHallEffect();
int addGreatHallCard(int, struct gameState *);

int main()
{
  testGreatHallEffect();
}

void testGreatHallEffect()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 30, &G);

  int bonus = 0;
  int greatHallCardPos = addGreatHallCard(0, &G);
  int numberOfCards = G.handCount[0],
      numActions = G.numActions;

  cardEffect(great_hall, 0, 0, 0, &G, greatHallCardPos, &bonus);

  assert_that(equals(G.handCount[0], numberOfCards + 1 - 1), "testGreatHallEffect", "The Great Hall card was removed and a card was drawn from the player's deck.");
  assert_that(equals(G.numActions, numActions + 1), "testGreatHallEffect", "The number of game actions was increased by 1");
}

int addGreatHallCard(int player, struct gameState *state)
{
  int i = 0;

  for (; i < state->handCount[player]; i++)
  {
    if (state->hand[player][i] == great_hall)
    {
      return i;
    }
  }

  state->hand[player][i] = great_hall;
  state->handCount[player]++;

  return i;
}