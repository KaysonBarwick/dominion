#include <iostream>
#include <vector>

#include "strategy/strategy.hpp"
#include "strategy/money.hpp"
#include "strategy/random.hpp"
#include "strategy/input.hpp"
#include "game.hpp"

int main(int argc, char **argv){
    srand(time(NULL));

    InputStrategy inputStrategy = InputStrategy();
    MoneyStrategy moneyStrategy = MoneyStrategy();
    RandomStrategy strategy = RandomStrategy();
    std::vector<Strategy*> strategies{
        &inputStrategy,
        &moneyStrategy,
        &strategy,
        &strategy,
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
