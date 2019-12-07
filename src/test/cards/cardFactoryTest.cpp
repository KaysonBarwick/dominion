#include <gtest/gtest.h>
#include "../../main/cards/cardFactory.hpp"
 
TEST(CardFactoryTest, getCard) { 
    ASSERT_EQ(CardFactory::getCard(0).getName(),  "Estate");
    ASSERT_EQ(CardFactory::getCard(4).getName(),  "Copper");
    ASSERT_EQ(CardFactory::getCard(7).getName(),  "Village");
    ASSERT_EQ(CardFactory::getCard(-1).getName(), "Province");
}
