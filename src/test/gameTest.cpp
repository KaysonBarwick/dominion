#include <gtest/gtest.h>
#include <vector>
#include <chrono>
#include <future>

#include "../main/game.hpp"
#include "../main/strategy/money.hpp"
#include "../main/strategy/random.hpp"
#include "../main/strategy/strategy.hpp"

class EmptyPilesStrategy : public Strategy{
    virtual void playCards(Player& player){}
    virtual void buyCards(Player& player, Supply& supply){
        while(supply.buyCard(Estate())){}
        while(supply.buyCard(Duchy())){}
        while(supply.buyCard(Curse())){}
    }
};

class EmptyProvinceStrategy : public Strategy{
    virtual void playCards(Player& player){}
    virtual void buyCards(Player& player, Supply& supply){
        while(supply.buyCard(Province())){}
    }
};

TEST(GameTest, RunGame) {
    srand(time(NULL));
    testing::internal::CaptureStdout(); // We don't want to see console output

    MoneyStrategy moneyStrategy = MoneyStrategy();
    RandomStrategy strategy = RandomStrategy();

    std::vector<Strategy*> strategies{
        &moneyStrategy,
        &strategy,
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

    Game game = Game(strategies, cards);

    auto asyncFuture = std::async(std::launch::async, [&game]() { game.play();});
    EXPECT_TRUE(asyncFuture.wait_for(std::chrono::milliseconds(5000)) != std::future_status::timeout);
    

    testing::internal::GetCapturedStdout();
}

TEST(GameTest, PilesEmpty){
    EmptyPilesStrategy strategy = EmptyPilesStrategy();

    std::vector<Strategy*> strategies{ &strategy };
    std::vector<Card> cards{};

    Game game = Game(strategies, cards);

    testing::internal::CaptureStdout(); // We don't want to see console output

    auto asyncFuture = std::async(std::launch::async, [&game]() { game.play();});
    EXPECT_TRUE(asyncFuture.wait_for(std::chrono::milliseconds(5000)) != std::future_status::timeout);

    testing::internal::GetCapturedStdout();
}

TEST(GameTest, ProvincesEmpty){
    EmptyProvinceStrategy strategy = EmptyProvinceStrategy();

    std::vector<Strategy*> strategies{ &strategy };
    std::vector<Card> cards{};

    Game game = Game(strategies, cards);

    testing::internal::CaptureStdout(); // We don't want to see console output

    auto asyncFuture = std::async(std::launch::async, [&game]() { game.play();});
    EXPECT_TRUE(asyncFuture.wait_for(std::chrono::milliseconds(5000)) != std::future_status::timeout);

    testing::internal::GetCapturedStdout();
}

