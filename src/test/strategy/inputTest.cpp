#include <gtest/gtest.h>
#include <vector>
#include <sstream>

#include "../../main/strategy/input.hpp"

TEST(InputStrategyTest, buySilver) {
    InputStrategy strategy = InputStrategy();
    Supply supply = Supply();
    std::vector<Card> cards{Village(), Festival(), Woodcutter()};
    supply.setSupplyCards(cards);
    supply.initSupply(4);

    testing::internal::CaptureStdout(); // We don't want to see console output

    Player player = Player();
    player.startNewTurn();
    
    std::istringstream istr("done 4"); // 4 is Copper, which we can always buy since 0
    strategy.playCards(player, istr);
    strategy.buyCards(player, supply, istr);

    ASSERT_EQ(9998, supply.howManyAvailable(Copper()));

    testing::internal::GetCapturedStdout();
}

