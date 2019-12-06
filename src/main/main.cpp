#include <iostream>
#include <vector>

#include "strategy.hpp"
#include "game.hpp"

int main(int argc, char **argv){
    srand(time(NULL));

    MoneyStrategy moneyStrategy = MoneyStrategy();
    Strategy strategy = Strategy();
    std::vector<Strategy*> strategies{
        &moneyStrategy,
        &strategy,
        &strategy,
        &strategy
    };

    std::vector<Card> cards{
        Village(),
        Smithy(),
        Festival(),
        Laboratory(),
        Market(),
        Woodcutter()
    };

    Game(strategies, cards).play();
}
