#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <unistd.h>

#include "cards/card.hpp"
#include "cards/supply.hpp"
#include "cards/cardFactory.hpp"

#define MCW MPI_COMM_WORLD

class Player {
  private:
    int actions = 1;
    int buys = 1;
    int money = 0;

    std::vector<Card> hand;
    std::vector<Card> deck;
    std::vector<Card> discard = CardFactory::getStarterCards();

    void shuffle(){
        deck.insert(deck.end(), discard.begin(), discard.end());
        discard.clear();
        std::random_shuffle(deck.begin(), deck.end());
    }

    void drawCard(){
        if(!deck.size()){
            shuffle();
            if(!deck.size()){
                // No cards left to draw!
                return;
            }
        }
        hand.push_back(deck.back());
        deck.pop_back();
    }

  public:
    int getBuys(){ return buys; }
    int getMoney(){ return money; }
    int getActions(){ return actions; }
    std::vector<Card> getHand(){
        std::vector<Card> ret(hand.size());
        std::copy(hand.begin(), hand.end(), ret.begin());
        return ret;
    }

    void startNewTurn(){
        discard.insert(discard.end(), hand.begin(), hand.end());
        hand.clear();
        actions = 1;
        buys = 1;
        money = 0;
        for(int i = 0; i < 5; ++i){
            drawCard();
        }
    }

    bool buyCard(Supply& supply, Card card){
        if(buys && money >= card.getCost() && supply.buyCard(card)){
            std::cout << "  *Bought " << card.getName() << std::endl;
            discard.push_back(card);
            buys--;
            money -= card.getCost();
            return true;
        }
        return false;
    }

    bool useCard(int index){
        if(index < hand.size() && index >= 0){
            Card card = hand[index];
            if(card.getType() == Action && actions){
                actions--;
            } else if (card.getType() == Money){
                // Do nothing for a money card
            } else if(card.getType() == Victory){
                // Do nothing for victory card
            } else {
                return false;
            }

            std::cout << "  Played " << card.getName() << std::endl;
            usleep(350000);

            buys += card.getBuys();
            money += card.getMoney();
            actions += card.getActions();
            for(int i = 0; i < card.getDraws(); ++i){
                drawCard();
            }

            discard.push_back(card);
            hand.erase(hand.begin() + index);

            return true;
        }
        return false;
    }

    int getScore(){
        int score = 0;
        for(int i = 0; i < hand.size(); ++i)    score += hand[i].getPoints();
        for(int i = 0; i < deck.size(); ++i)    score += deck[i].getPoints();
        for(int i = 0; i < discard.size(); ++i) score += discard[i].getPoints();
        return score;
    }
};
