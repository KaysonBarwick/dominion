#pragma once

#include<string>

enum CardType {
    Action,
    Money,
    Victory
};

class Card {
    protected:
      std::string name = "Card";
      int id = -1;
      CardType type = Victory;
      int cost = 999;
      int points = 0;

      int actions = 0;
      int buys = 0;
      int draws = 0;
      int money = 0;

    public:
      std::string getName(){ return name; }
      int getId(){ return id; }
      CardType getType(){ return type; }
      int getCost(){ return cost; }
      int getPoints(){ return points; }

      int getActions(){ return actions; }
      int getBuys(){ return buys; }
      int getDraws(){ return draws; }
      int getMoney(){ return money; }

    bool operator==(const Card& other) const {
      return name == other.name && id == other.id;
    }

};
