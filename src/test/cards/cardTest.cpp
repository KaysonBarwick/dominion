#include <gtest/gtest.h>
#include "../../main/cards/cards.hpp"
 
TEST(CardTest, getStats) { 
    Card card = Woodcutter();
    ASSERT_EQ(card.getName(), "Woodcutter");
    ASSERT_EQ(card.getId(), 12);
    ASSERT_EQ(card.getType(), Action);
    ASSERT_EQ(card.getCost(), 3);
    ASSERT_EQ(card.getBuys(), 1);
    ASSERT_EQ(card.getMoney(), 2);
    ASSERT_EQ(card.getPoints(), 0);
}


