#pragma once

#include <iostream>
#include <string>

#include "../cards/card.hpp"
#include "../player.hpp"
#include "strategy.hpp"

class InputStrategy : public Strategy {
  private:
    void printCardStats(Card card){
        if(card.getDraws() > 0)   std::cout << "  +"  << card.getDraws()   << " Card(s)";
        if(card.getActions() > 0) std::cout << "  +"  << card.getActions() << " Action(s)";
        if(card.getBuys() > 0)    std::cout << "  +"  << card.getBuys()    << " Buy(s)";
        if(card.getMoney() > 0)   std::cout << "  +(" << card.getMoney()   << ")";
        if(card.getPoints() != 0) std::cout << "  "   << card.getPoints()  << "VP";
    }

    void printHand(Player player){
        std::cout << std::endl;

        std::vector<Card> hand = player.getHand();
        for(int i = 0; i < hand.size(); ++i){
            std::cout << "  " << i << ": " << hand[i].getName();
            this->printCardStats(hand[i]);
            std::cout << std::endl;
        }
    }

    void printSupply(Supply supply){
        std::cout << "----------------" << std::endl;

        std::vector<Card> supplyCards = supply.getSupplyCards();
        for(int i = 0; i < supplyCards.size(); ++i){
            Card card = supplyCards[i];
            
            std::cout << "  " << i << ": "
                      << "*Cost: " << card.getCost() << "* "
                      << card.getName()
                      << "(" << supply.howManyAvailable(card) << ")";
            this->printCardStats(card);
            std::cout << std::endl;
        }

        std::cout << "----------------" << std::endl;
    }

  public:
    virtual void playCards(Player& player){
        std::string input = "";
        std::vector<Card> hand = player.getHand();

        while(player.getHand().size() > 0){

            this->printHand(player);
            std::cout << "What card would you like to play? (enter 'done' when finished): ";
            std::cin >> input;

            if(input == "done"){
                break;
            } else {
                try {
                    int number = std::stoi(input);
                    if(number < hand.size()){
                        player.useCard(number);
                    } else {
                        std::cout << "You cannot play that!" << std::endl;
                    }
                } catch(std::invalid_argument const &e){
                    std::cout << "Input must be a number between 0 and " << hand.size() << std::endl;
                }
            }
            hand = player.getHand();
        }

        // Play all treasures automatically for buying
        for(int i = hand.size() - 1; i >= 0; --i){
            if(hand[i].getType() == Money){
                player.useCard(i);
            }
        }
    }

    virtual void buyCards(Player& player, Supply& supply){

        std::vector<Card> supplyCards = supply.getSupplyCards();
        std::string input = "";

        this->printSupply(supply);
        while(player.getBuys()){
            std::cout << std::endl << "You have (" << player.getMoney() << ") and " << player.getBuys() << " buys." << std::endl;
            std::cout << "What card would you like to buy? (enter 'done' when finished): ";
            std::cin >> input;
            if(input == "done"){
                break;
            } else {
                try {
                    int number = std::stoi(input);
                    if(number < supplyCards.size()){
                        if(!player.buyCard(supply, CardFactory::getSupplyCard(supply, number))){
                            std::cout << "You cannot buy that!" << std::endl;
                        }
                    }
                } catch(std::invalid_argument const &e){
                    std::cout << "Input must be a number between 0 and " << supplyCards.size() << std::endl;
                }
            }
        }
    }
};
