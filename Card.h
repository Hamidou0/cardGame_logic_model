#pragma once

#include <iostream>
#include <string>
#include <fstream>



using namespace std;
class Card{

public:
    //name of the card
    string name;
    //will be implemented by the sub-class (Blue, Chili,Stink,...), this is why it is ...=0
    virtual int getCardsPerCoin(int coins) =0;
    //will be implemented by the sub-class (Blue, Chili,Stink,...), this is why it is ...=0
    virtual string getName() =0 ;
    //will be implemented by the sub-class, print the first character of the card
    virtual void print(std::ostream& out)  =0;
    //friend function inline for the outgoing stream 
    friend std::ostream& operator<< (std::ostream& out, Card& card) { 
		card.print(out);
		return out;
	};
};

