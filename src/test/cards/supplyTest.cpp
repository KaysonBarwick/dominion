#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

#include "../../main/cards/supply.hpp"
 
TEST(SupplyTest, buyCard) {
    Supply supply = Supply();

    std::vector<Card> cards{Village(), Festival(), Woodcutter()};
    supply.setSupplyCards(cards);

    std::vector<Card> expectedCards{Estate(), Duchy(), Province(), Curse(), Copper(), Silver(), Gold()};
    expectedCards.insert(expectedCards.end(), cards.begin(), cards.end());

    EXPECT_THAT(supply.getSupplyCards(), ::testing::ElementsAreArray(expectedCards));

    supply.initSupply(4);
    ASSERT_EQ(10, supply.howManyAvailable(Woodcutter()));

    // Buy all of the woodcutters
    for(int i = 1; i <= 10; ++i){
        ASSERT_TRUE(supply.buyCard(Woodcutter()));
        ASSERT_EQ(10 - i, supply.howManyAvailable(Woodcutter()));
    }
    
    ASSERT_FALSE(supply.buyCard(Woodcutter()));
    ASSERT_EQ(1, supply.howManyEmptyPiles());
}