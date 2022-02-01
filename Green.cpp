//includeing the parent class
#include "Card.h"
#include <string.h>
//extending the parent class
class Green : public Card{

    public:

        static const int total_cards = (int) 14 ;
//return coins per card
        int getCardsPerCoin(int coins){
            if (coins==1) return 3;
            else if (coins==2) return 5;
            else if (coins==3) return 6;
            else if (coins==4) return 7;
            else return -1;
        
        }
        //return name of the card
        std::string getName(){
            return "Green";
        }
        //print the first letter of the card
        void print(std::ostream& out) {
            out<<"G";
        }



};