#pragma once

#include <vector>

#include "cards.hpp"
#include "card.hpp"
#include "supply.hpp"

class CardFactory {
  public:
    static Card getCard(int id){
        if(id == 0){ return Estate();   }
        if(id == 1){ return Duchy();    }
        if(id == 2){ return Province(); }
        if(id == 3){ return Curse();    }

        if(id == 4){ return Copper(); }
        if(id == 5){ return Silver(); }
        if(id == 6){ return Gold();   }

        if(id == 7) { return Village();    }
        if(id == 8) { return Smithy();     }
        if(id == 9) { return Festival();   }
        if(id == 10){ return Laboratory(); }
        if(id == 11){ return Market();     }
        if(id == 12){ return Woodcutter(); }

        return Province(); //Default to most valuable card, just to be nice ;)
    }

    static Card getSupplyCard(Supply supply, int index){
        std::vector<Card> supplyCards = supply.getSupplyCards();
        if(index >= supplyCards.size()){
            return Province(); //Default to most valuable card, just to be nice ;)
        }
        return supplyCards[index];
    }

    static std::vector<Card> getStarterCards(){
        return std::vector<Card>{
            Estate(), Estate(), Estate(),
            Copper(), Copper(), Copper(), Copper(), Copper(), Copper(), Copper()
        };
    }
};
