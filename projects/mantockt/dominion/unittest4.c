#include "dominion.h"
#include "dominion_helpers.h"
#include "assertion.h"

void testAdventurerShuffle();
int addAdventurerCard(int, struct gameState *);
void discardCardsFromDeck(int, struct gameState *);
int numberOfTreasureFromEndOfHand(int, struct gameState *, int);

int main()
{
  testAdventurerShuffle();
}

void testAdventurerShuffle()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 30, &G);

  addAdventurerCard(0, &G);
  discardCardsFromDeck(0, &G);

  int discardCount = G.discardCount[0];
  int copyDiscarded[discardCount];

  array_copy(G.discard[0], discardCount, copyDiscarded, discardCount);

  copyDiscarded[discardCount] = G.deck[0][0]; // Get the last card in the deck

  adventurer_effect(0, &G);

  assert_that(greater_than(G.deckCount[0], 1), "testAdventurerShuffle", "Cards were added to the deck.");
  assert_that(equals(G.deckCount[0], discardCount), "testAdventurerShuffle", "The discarded cards were added to the remaining card in the deck.");
  assert_that(deep_equals(G.deck[0], G.deckCount[0], copyDiscarded, discardCount), "testAdventurerShuffle", "All the cards from discarded are added to the deck.");
}

void discardCardsFromDeck(int player, struct gameState *state)
{
  int i = 0;
  while (state->deckCount[player] > 0)
  {
    state->discard[player][i] = state->hand[player][state->deckCount[player] - 1];
    state->hand[player][--state->deckCount[player]] = -1;
    state->discardCount[player]++;
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