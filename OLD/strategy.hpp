#pragma once

#include <stdlib.h>
#include "player.hpp"
#include "cards.hpp"

class Strategy {
  public:
    virtual void playCards(Player& player){
        bool cardPlayed = true;
        while(cardPlayed){
            cardPlayed = false;
            std::vector<Card> hand = player.getHand();
            for(int i = 0; i < hand.size(); ++i){
                if(player.useCard(i)){
                    cardPlayed = true;
                }
            }
        }
    }

    virtual void buyCards(Player& player){
        player.buyCard(Province());
        int tries = 10;
        while(tries-- && player.getBuys()){
            int toBuy = rand() % 13;
            if(toBuy != 3) player.buyCard(getCard(toBuy));
        }

    }
};

class MoneyStrategy : public Strategy {
  public:
    void buyCards(Player& player){
        player.buyCard(Province());
        player.buyCard(Gold());
        player.buyCard(Duchy());
        player.buyCard(Silver());
    }
};
