#pragma once

#include <iostream>
#include "Deck.h"

#include "Blue.cpp"
#include "black.cpp"
#include "Chili.cpp"
#include "garden.cpp"
#include "Green.cpp"
#include "Red.cpp"
#include "soy.cpp"
#include "Stink.cpp"

using namespace std;

class CardFactory{

    //creating a deck object 
    Deck deck;

    //this function adds all the cards in the deck (depending on their total cards value)
    void addSets(){
        for(int i = 0; i < Blue::total_cards; i++){
            Card* temp = new Blue;
            deck.push_back(temp);
        }
        for(int i = 0; i < black::total_cards; i++){
            Card* temp = new black;
            deck.push_back(temp);
        }
        for(int i = 0; i < Chili::total_cards; i++){
            Card* temp = new Chili;
            deck.push_back(temp);
        }
        for(int i = 0; i < garden::total_cards; i++){
            Card* temp = new garden;
            deck.push_back(temp);
        }
        for(int i = 0; i < Green::total_cards; i++){
            Card* temp = new Green;
            deck.push_back(temp);
        }
        for(int i = 0; i < Red::total_cards; i++){
            Card* temp = new Red;
            deck.push_back(temp);
        }
        for(int i = 0; i < soy::total_cards; i++){
            Card* temp = new soy;
            deck.push_back(temp);
        }
        for(int i = 0; i < Stink::total_cards; i++){
            
            Card* temp = new Stink();
            deck.push_back(temp);
        }
        
        
    } 
    public:
        CardFactory();
        static CardFactory* getFactory();
        Deck getDeck();
        void addToDeck();
        Card* getCard(char);
};

//given the first letter of a card, return the card object corresponding
Card* CardFactory::getCard(char type) {  
	Card * newCard = NULL;

	if (type == 'b') {
		newCard = new black();
	}
	else if (type == 'B') {
		newCard = new Blue();
	}
	else if (type =='C') {
		newCard = new Chili();
	}
	else if (type == 'g') {
		newCard = new garden();
	}
	else if (type == 'G') {
		newCard = new Green();
	}
	else if (type == 'R') {
		newCard = new Red();
	}
	else if (type == 's') {
		newCard = new soy();
	}
	else if (type == 'S') {
		newCard = new Stink();
	}

	return newCard;

}

//constructor
CardFactory::CardFactory(){
    addSets();
}

//returns a cardfactory object
CardFactory * CardFactory::getFactory()
{
	static CardFactory cf;
	return &cf;
}

//shuffles the deck and returns it 
Deck CardFactory::getDeck(){

    deck.shuffle();
    return deck;
}
