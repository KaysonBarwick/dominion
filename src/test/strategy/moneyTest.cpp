#include <gtest/gtest.h>
#include <vector>

#include "../../main/strategy/money.hpp"
 
TEST(MoneyStrategyTest, buySilver) {
    MoneyStrategy strategy = MoneyStrategy();
    Supply supply = Supply();

    std::vector<Card> cards{Village(), Festival(), Woodcutter()};

    srand(time(NULL));
    testing::internal::CaptureStdout(); // We don't want to see console output
    for(int i = 0; i < 100; ++i){ // Try 100 times to account for randomness
        supply.setSupplyCards(cards);
        supply.initSupply(4);
        ASSERT_EQ(9999, supply.howManyAvailable(Silver()));

        // Take two turns, guarenteed to buy at least one silver, possibly two
        // 5-2 copper start vs 4-3 copper start
        Player player = Player();
        player.startNewTurn();
        strategy.playCards(player);
        strategy.buyCards(player, supply);

        player.startNewTurn();
        strategy.playCards(player);
        strategy.buyCards(player, supply);

        ASSERT_LT(supply.howManyAvailable(Silver()), 9999);
    }
    testing::internal::GetCapturedStdout();
}
