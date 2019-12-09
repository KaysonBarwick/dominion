#pragma once

#include <vector>

#include "card.hpp"
#include "cards.hpp"

class Supply {
  private:
    std::vector<Card> cards;
    std::vector<int> cardCounts;

    const int MONEYCOUNT = 9999;
    const int VICTORYCOUNT = 4;
    const int CURSECOUNT = 10;
    const int SUPPLYCOUNT = 10;

    void addBasicCards(){
        this->cards.push_back(Estate());
        this->cards.push_back(Duchy());
        this->cards.push_back(Province());
        this->cards.push_back(Curse());

        this->cards.push_back(Copper());
        this->cards.push_back(Silver());
        this->cards.push_back(Gold());
    }

  public:
    void setSupplyCards(std::vector<Card> cards){
        this->cards.clear();
        this->addBasicCards();
        this->cards.insert(this->cards.end(), cards.begin(), cards.end());
    }

    void initSupply(int numPlayers){
        this->cardCounts.clear();
        for(int i = 0; i < this->cards.size(); ++i){
            Card card = this->cards[i];
            if(card.getType() == Victory){
                this->cardCounts.push_back(numPlayers * VICTORYCOUNT);
            } else if(card.getName() == "Curse"){
                this->cardCounts.push_back(numPlayers * CURSECOUNT);
            } else if(card.getType() == Money){
                this->cardCounts.push_back(MONEYCOUNT);
            } else {
                this->cardCounts.push_back(SUPPLYCOUNT);
            }
        }
    }

    std::vector<Card> getSupplyCards(){
        return cards;
    }

    int howManyEmptyPiles(){
        int empty = 0;
        for(int i = 0; i < this->cardCounts.size(); ++i){
            if(this->cardCounts[i] <= 0){
                empty++;
            }
        }
    
        return empty;
    }

    int howManyAvailable(Card card){
        for(int i = 0; i < this->cards.size(); ++i){
            if(card.getName() == this->cards[i].getName()){
                return this->cardCounts[i];
            }
        }

        return 0;
    }

    bool buyCard(Card toBuy){
        for(int i = 0; i < this->cards.size(); ++i){
            if(toBuy.getName() == this->cards[i].getName() && this->cardCounts[i] > 0){
                this->cardCounts[i]--;
                return true;
            }
        }
        return false;
    }
};
