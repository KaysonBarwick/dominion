#pragma once

#include "card.hpp"
#include <vector>
#include <string>

class Estate: public Card {
  public:
    Estate(){
        name = "Estate";
        id = 0;
        cost = 2;
        points = 1;
    }
};

class Duchy: public Card {
  public:
    Duchy(){
        name = "Duchy";
        id = 1;
        cost = 5;
        points = 3;
    }
};

class Province: public Card {
  public:
    Province(){
        name = "Province";
        id = 2;
        cost = 8;
        points = 6;
    }
};

class Curse: public Card {
  public:
    Curse(){
        name = "Curse";
        id = 3;
        cost = 0;
        points = -1;
    }
};

class Copper: public Card {
  public:
    Copper(){
        name = "Copper";
        id = 4;
        type = Money;
        cost = 0;
        money = 1;
    }
};

class Silver: public Card {
  public:
    Silver(){
        name = "Silver";
        id = 5;
        type = Money;
        cost = 3;
        money = 2;
    }
};

class Gold: public Card {
  public:
    Gold(){
        name = "Gold";
        id = 6;
        type = Money;
        cost = 6;
        money = 3;
    }
};

class Village: public Card {
  public:
    Village(){
        name = "Village";
        id = 7;
        type = Action;
        cost = 3;
        draws = 1;
        actions = 2;
    }
};

class Smithy: public Card {
  public:
    Smithy(){
        name = "Smithy";
        id = 8;
        type = Action;
        cost = 4;
        draws = 3;
    }
};

class Festival: public Card {
  public:
    Festival(){
        name = "Festival";
        id = 9;
        type = Action;
        cost = 5;
        actions = 2;
        buys = 1;
        money = 2;
    }
};

class Laboratory: public Card {
    public:
    Laboratory(){
        name = "Laboratory";
        id = 10;
        type = Action;
        cost = 5;
        actions = 1;
        draws = 2;
    }
};

class Market: public Card {
  public:
    Market(){
        name = "Market";
        id = 11;
        type = Action;
        cost = 5;
        actions = 1;
        buys = 1;
        draws = 1;
        money = 1;
    }
};

class Woodcutter: public Card {
  public:
    Woodcutter(){
        name = "Woodcutter";
        id = 12;
        type = Action;
        cost = 3;
        buys = 1;
        money = 2;
    }
};
