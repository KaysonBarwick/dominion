#pragma once

#include "strategy.hpp"

class MoneyStrategy : public Strategy {
  public:
    virtual void playCards(Player& player){
        std::vector<Card> hand = player.getHand();
        for(int i = 0; i < hand.size(); ++i){
            player.useCard(0);
        }
    }

    virtual void buyCards(Player& player, Supply& supply){
        player.buyCard(supply, Province());
        player.buyCard(supply, Gold());
        player.buyCard(supply, Duchy());
        player.buyCard(supply, Silver());
    }
};
