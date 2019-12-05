#pragma once

#include <mpi.h>
#include <iostream>

#include "player.hpp"
#include "strategy.hpp"

#define MCW MPI_COMM_WORLD

void manage(){
    int size;
    MPI_Comm_size(MCW, &size);

    std::vector<int> cards = {
        //victory cards
        size * 4, size * 4, size * 4, 40,
        //money cards
        99, 99, 99, 99,
        //other cards
        10, 10, 10, 10, 10, 10, 10, 10, 10, 10
    };
    int emptyPiles = 0;
    bool end = false;
    while(!end){
        int toBuy;
        MPI_Status status;
        MPI_Recv(&toBuy, 1, MPI_INT, MPI_ANY_SOURCE, 0, MCW, &status);
        if(toBuy < cards.size() && toBuy >= 0 && cards[toBuy]){
            cards[toBuy]--;
            if(!cards[toBuy]){
                emptyPiles++;
            }
        } else {
            toBuy = -1;
        }
        MPI_Send(&toBuy, 1, MPI_INT, status.MPI_SOURCE, 0, MCW);

        std::cout << "Process " << status.MPI_SOURCE << " is buying " << toBuy << std::endl;
        std::cout << "Stock ";
        for(int i = 0; i < cards.size(); ++i) std::cout << " " << cards[i];
        std::cout << std::endl;

        if(!cards[2] || emptyPiles >= 3){
            std::cout << "Awe man! The games over!" << std::endl;
            toBuy = -1;
            end = true;
            //out of province cards, or empty piles game end!
            for(int i = 1; i < size; ++i){
                MPI_Send(&toBuy, 1, MPI_INT, i, 0, MCW); // Tell all processes they can't buy
                MPI_Send(NULL, 0, MPI_INT, i, 1, MCW);
            }
        }
    }

    std::vector<int> scores(size);
    for(int i = 1; i < size; ++i){
        MPI_Recv(&scores[i], 1, MPI_INT, i, 2, MCW, MPI_STATUS_IGNORE);
        std::cout << "Player " << i << " got a score of " << scores[i] << std::endl;
    }
}

void play(Strategy* strategy){
    Player player = Player();
    while(!player.isGameOver()){
        player.startNewTurn();
        strategy->playCards(player);
        strategy->buyCards(player);
    }
    int score = player.getScore();
    MPI_Send(&score, 1, MPI_INT, 0, 2, MCW);
}

