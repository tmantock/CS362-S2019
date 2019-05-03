#include "assertion.h"
#include "dominion.h"

void testStewardEffectChoice1();
void testStewardEffectChoice2();
void testStewardEffectChoice3();
int addStewardCard(int, struct gameState *);
int cardNotInHand(int, int, struct gameState *);
int getDiscardableCard(int, int, int, struct gameState *);

int main()
{
  testStewardEffectChoice1();
  testStewardEffectChoice2();
  testStewardEffectChoice3();
}

void testStewardEffectChoice1()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 30, &G);

  int bonus = 0,
      coins = G.coins;
  int stewardCardPos = addStewardCard(0, &G);
  int numberOfCards = G.handCount[0];

  cardEffect(steward, 1, 0, 0, &G, stewardCardPos, &bonus);

  assert_that(equals(G.coins, coins), "testStewardEffectChoice1", "The coins amount was not changed");
  assert_that(equals(G.handCount[0], numberOfCards + 2 - 1), "testStewardEffectChoice1", "The player drew 2 cards and discarded the Steward card");
}

void testStewardEffectChoice2()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 30, &G);

  int bonus = 0,
      coins = G.coins;
  int stewardCardPos = addStewardCard(0, &G);
  int numberOfCards = G.handCount[0];

  cardEffect(steward, 2, 0, 0, &G, stewardCardPos, &bonus);

  assert_that(equals(G.coins, coins + 2), "testStewardEffectChoice2", "The coins amount was increased by 2");
  assert_that(equals(G.handCount[0], numberOfCards - 1), "testStewardEffectChoice2", "No new cards were drawn and the Steward card was removed.");
}

void testStewardEffectChoice3()
{
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
               sea_hag, tribute, smithy};

  initializeGame(2, k, 30, &G);

  int bonus = 0,
      coins = G.coins;
  int stewardCardPos = addStewardCard(0, &G);
  int numberOfCards = G.handCount[0];
  int discardOne = getDiscardableCard(0, 0, stewardCardPos, &G);
  int discardTwo = getDiscardableCard(0, discardOne + 1, stewardCardPos, &G);
  int discardedCardOne = G.hand[0][discardOne],
      discardedCardTwo = G.hand[0][discardTwo];

  printf("%d - %d", discardedCardOne, discardedCardTwo);

  cardEffect(steward, 3, discardOne, discardTwo, &G, stewardCardPos, &bonus);

  assert_that(equals(G.coins, coins), "testStewardEffectChoice3", "The amount coins was not changed");
  assert_that(equals(G.handCount[0], numberOfCards - 2 - 1), "testStewardEffectChoice3", "The two cards were discarded along with the Steward card.");
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

int getDiscardableCard(int player, int start, int ignore, struct gameState *state)
{
  for (int i = start; i < state->handCount[player]; i++)
  {
    if (state->hand[player][i] != ignore)
    {
      return i;
    }
  }

  return -1;
}

int cardNotInHand(int player, int card, struct gameState *state)
{
  for (int i = 0; i < state->handCount[player]; i++)
  {
    if (state->hand[player][i] == card)
    {
      return 0;
    }
  }

  return 1;
}
