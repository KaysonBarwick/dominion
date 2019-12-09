#include <gtest/gtest.h>
#include <vector>

#include "../main/player.hpp"

TEST(PlayerTest, BuyEstate) {
    Supply supply = Supply();
    std::vector<Card> cards{};
    supply.setSupplyCards(cards);
    supply.initSupply(4);

    srand(time(NULL));
    testing::internal::CaptureStdout(); // We don't want to see console output
    
    Player player = Player();
    player.startNewTurn();
    
    std::vector<Card> hand = player.getHand();
    for(int i = hand.size(); i >= 0; --i){ // Play all cards
        player.useCard(i);
    }
    player.buyCard(supply, Estate()); //guarenteed to buy since only costs 2

    testing::internal::GetCapturedStdout();

    ASSERT_EQ(4, player.getScore()); //3 starting estates +1 bought
}
