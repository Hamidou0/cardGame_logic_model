#pragma once
#include <iostream>
#include "Card.h"
#include "CardFactory.h"
#include <list>
#include <vector>
using namespace std;

class Hand : public std::vector<Card*>{

    
    public:
        Hand& operator+=(Card*); //add a card in last position  
        Card* play(); //return and delete the first card f the hand 
        Card* top(); //return but does not delete top card 
        Card* operator[](int n);  //return and delte card at a given position 
        void print(std::ostream&); //prints everything about the hand, display all the cards in order
        friend ostream & operator << (ostream &, Hand&); //friend funcrion to print the hand 
        Hand(istream& in, CardFactory *cf);//constructor 
        Hand(); // default constructor
};

Hand::Hand(istream& in, CardFactory *cf){
    //creating an array that contains char for the hand
    char cardsHand[256];
    in>>cardsHand;
    

    //now we have an array of cards for the hand, we want t fing its length
    int a =0;
    while(cardsHand[a] != NULL){
        a++;
    }
    for (int i=(a-1);i>=0;i--){
        Card* newCard = ((*cf).getCard(cardsHand[i]));
        (*this).push_back(newCard);
    }
    

};

//Constructor 
Hand::Hand(){
    (*this).clear();
};

//returns top card of the hand 
Card* Hand::top(){
    return (*this).back();
}

//remove and return last card of the hand 
Card* Hand::play(){
    
    Card* temp = (*this).back();
    (*this).pop_back();
    return temp;
}

//returns elmeent at position i 
Card* Hand::operator[](int i){
    Card* temp = (*this).at((*this).size()-i);
    (*this).erase((*this).begin()+ (*this).size()-i );
    return temp;
}

//add card to the hand 
Hand& Hand ::operator+=(Card* newCard) {  
	(*this).insert(begin(), newCard);
	return *this;

}

//insertion operator
ostream& operator<<(ostream& outstream,Hand &hand){
    
    
    //because the beginning of he hand is the end of the list, we have to go down
    //we use the iterator to go down the list 
    
	for (vector<Card*>::reverse_iterator it = hand.rbegin(); it != hand.rend(); it++) {
		(*it)->print(outstream);
	}
	return outstream;
}

//print the hand 
void Hand::print(ostream& out){
    for (vector<Card*>::reverse_iterator it = (*this).rbegin(); it != (*this).rend(); it++) {
		(*it)->print(out);
        out<<" ";

	}
    out<<endl;
}

