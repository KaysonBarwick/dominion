#pragma once

#include "strategy.hpp"

class RandomStrategy : public Strategy {
  public:
    virtual void playCards(Player& player){
        std::vector<Card> hand = player.getHand();
        for(int i = hand.size(); i >= 0; --i){
            if(player.useCard(i) && hand[i].getDraws() > 0){
                hand = player.getHand();
                i = hand.size();
            }
        }
    }

    virtual void buyCards(Player& player, Supply& supply){
        player.buyCard(supply, CardFactory::getCard(2)); // Prefer buying Province
        int tries = 10;
        while(tries-- && player.getBuys()){
            int toBuy = rand() % 13;
            if(toBuy != 3) player.buyCard(supply, CardFactory::getCard(toBuy));
        }
    }
};
