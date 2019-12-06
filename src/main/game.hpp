#pragma once

#include <iostream>
#include <vector>

#include "player.hpp"
#include "strategy.hpp"
#include "cards/supply.hpp"

#define MCW MPI_COMM_WORLD

class Game {
  private:
    Supply supply = Supply();
    std::vector<Strategy*> playerStrategies;
    std::vector<Player> players;

  public:
    Game(std::vector<Strategy*> playerStrategies, std::vector<Card> cards): playerStrategies(playerStrategies) {
        for(int i = 0; i < playerStrategies.size(); ++i){
            this->players.push_back(Player());
        }
        this->supply.setSupplyCards(cards);
    }

    bool isGameOver(){
        return this->supply.howManyEmptyPiles() >= 3 || this->supply.howManyAvailable(Province()) <= 0;
    }

    void play(){
        this->supply.initSupply(this->players.size());
        while(!this->isGameOver()){
            for(int i = 0; i < players.size(); ++i){
                std::cout << std::endl << "----------------" << std::endl;
                std::cout << "Player " << i << "'s turn." << std::endl;
                Strategy* strategy = this->playerStrategies[i];

                this->players[i].startNewTurn();
                strategy->playCards(this->players[i]);
                strategy->buyCards(this->players[i], this->supply);
            }
        }

        std::cout << std::endl << "----------------" << std::endl;
        for(int i = 0; i < players.size(); ++i){
            std::cout << "Player " << i << " scored " << players[i].getScore() << std::endl;
        }
    }

};
