//includeing the parent class
#include "Card.h"
#include <string.h>
//extending the parent class
class garden : public Card{

    public:

        static const int total_cards = (int) 6 ;
//return coins per card
        int getCardsPerCoin(int coins){
            
            if (coins==2) return 2;
            else if (coins==3) return 3;
            
            else return 0;
        
        }
        //return name of the card
        std::string getName(){
            return "garden";
        }
        //print the first letter of the card
        void print(std::ostream& out) {
            out<<"g";
        }



};