#include <gtest/gtest.h>
#include <vector>

#include "../../main/strategy/random.hpp"
 
int supplyCardCount(Supply supply){
    int count = 0;
    std::vector<Card> supplyCards = supply.getSupplyCards();
    for(int i = 0; i < supplyCards.size(); ++i){
        count += supply.howManyAvailable(supplyCards[i]);
    }
    return count;
}

TEST(RandomStrategyTest, buyStuff) {
    RandomStrategy strategy = RandomStrategy();
    Supply supply = Supply();
    std::vector<Card> cards{Village(), Festival(), Woodcutter()};
    supply.setSupplyCards(cards);
    supply.initSupply(4);

    int supplyCountBefore = supplyCardCount(supply);

    srand(time(NULL));
    testing::internal::CaptureStdout(); // We don't want to see console output
    Player player = Player();
    for(int i = 0; i < 20; ++i){ // take 20 turns to account for randomness and hope we buy stuff
        player.startNewTurn();
        strategy.playCards(player);
        strategy.buyCards(player, supply);
    }
    testing::internal::GetCapturedStdout();

    ASSERT_LT(supplyCardCount(supply), supplyCountBefore - 15); // Small chance we don't buy something on a turn.
}

