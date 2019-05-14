#include "dominion.h"
#include "assertion.h"

void testGreatHallDiscard();
int addGreatHallCard(int, struct gameState *);

int main()
{
  testGreatHallDiscard();
}

void testGreatHallDiscard()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 30, &G);

  int greatHallCardPos = addGreatHallCard(0, &G);
  int deckCount = G.deckCount[0],
      playedCount = G.playedCardCount;

  int returnValue = great_hall_effect(0, greatHallCardPos, &G);

  assert_that(equals(G.deckCount[0], deckCount - 1), "testGreatHallDiscard", "A card is drawn from the player's deck.");
  assert_that(equals(G.playedCardCount, playedCount + 1), "testGreatHallDiscard", "A card was added to the discarded deck");
  assert_that(equals(G.playedCards[G.playedCardCount - 1], great_hall), "testGreatHallDiscard", "The top card of the discard deck is the Great Hall card.");
  assert_that(equals(returnValue, 0), "testGreatHallDiscard", "The function returns 0.");
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