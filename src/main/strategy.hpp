#pragma once

#include <stdlib.h>

#include "player.hpp"
#include "cards/cards.hpp"
#include "cards/supply.hpp"

class Strategy {
  public:
    virtual void playCards(Player& player){
        bool cardPlayed;
        do {
            cardPlayed = false;
            std::vector<Card> hand = player.getHand();
            for(int i = 0; i < hand.size(); ++i){
                if(player.useCard(i)){
                    cardPlayed = true;
                }
            }
        } while(cardPlayed);
    }

    virtual void buyCards(Player& player, Supply& supply){
        player.buyCard(supply, Province());
        int tries = 10;
        while(tries-- && player.getBuys()){
            int toBuy = rand() % 13;
            if(toBuy != 3) player.buyCard(supply, getCard(toBuy));
        }

    }
};

class MoneyStrategy : public Strategy {
  public:
    virtual void buyCards(Player& player, Supply& supply){
        player.buyCard(supply, Province());
        player.buyCard(supply, Gold());
        player.buyCard(supply, Duchy());
        player.buyCard(supply, Silver());
    }
};
