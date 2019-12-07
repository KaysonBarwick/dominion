#pragma once

#include <stdlib.h>

#include "../player.hpp"
#include "../cards/supply.hpp"
#include "../cards/cardFactory.hpp"

class Strategy {
  public:
    virtual void playCards(Player& player) = 0;
    virtual void buyCards(Player& player, Supply& supply) = 0;
};
