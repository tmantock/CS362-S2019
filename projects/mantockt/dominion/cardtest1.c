#include "dominion.h"
#include "assertion.h"

void testAdventurerEffect();
int addAdventurerCard(int, struct gameState *);
int numberOfTreasureFromEndOfHand(int, struct gameState *, int);

int main()
{
  testAdventurerEffect();
}

void testAdventurerEffect()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 30, &G);

  int bonus = 0;
  int adventurerCardPosition = addAdventurerCard(0, &G);
  int numberOfCards = G.handCount[0];

  cardEffect(adventurer, 0, 0, 0, &G, adventurerCardPosition, &bonus);

  assert_that(equals(numberOfTreasureFromEndOfHand(0, &G, 3), 3), "testAdventurerEffect", "The last three cards in the player's hand are treasure cards");
  assert_that(equals(G.handCount[0], numberOfCards + 3 - 1), "testAdventurerEffect", "The player's hand has the three treasure cards and the adventurer card was removed");
}

int numberOfTreasureFromEndOfHand(int player, struct gameState *state, int n)
{
  int treasure = 0,
      numberOfCards = state->handCount[player];

  for (int i = numberOfCards - 1; i > (numberOfCards - 1) - n; i--)
  {
    if (state->hand[player][i] == copper || state->hand[player][i] == silver || state->hand[player][i] == gold)
    {
      treasure++;
    }
  }

  return treasure;
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