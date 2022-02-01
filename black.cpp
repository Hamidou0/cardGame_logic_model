//includeing the parent class
#include "Card.h"
#include <string.h>
//extending the parent class
class black : public Card{

    public:

        static const int total_cards = (int) 10 ;
        //return coins per card
        int getCardsPerCoin(int coins){
            if (coins==1) return 2;
            else if (coins==2) return 4;
            else if (coins==3) return 5;
            else if (coins==4) return 6;
            else return -1;
        
        }
        //return name of the card
        std::string getName(){
            return "black";
        }
        //print the first letter of the card
        void print(std::ostream& out) {
            out<<"b";
        }



};