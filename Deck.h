#pragma once

#include <vector>
#include <iostream>
#include "Card.h"
#include <vector>
#include "CardFactory.h"
#include <algorithm>
#include <random>

using namespace std;

class Deck : public vector<Card*>{
    
    public:
    /*
    ajoute un element a larriere du deck
    */
        void add(Card*);
    /*
     constructeur par defautf
     */
        Deck();
    /*
     constructeur deck de recopie
     */
        Deck(const Deck&);
    /*
     constructeur deck fichier .txt
     */
        //Deck(istream&, CardFactory*);
    /*
     melange les cartes du deck
     */
        void shuffle();
    /*
     supprime et retourne la carte superieur, draw()
     */
        Card* draw();
    /*
     inserer le deck dans un fichier externe
     */
        friend ostream& operator<<(ostream&, const Deck&);
    /*
     print the deck
    */
        void print(ostream&);    

};

//exception when the deck is empty but we try to draw a card from it
class DeckisEmpty : public exception
{
	virtual const char* what() const throw()
	{
		return "The deck is empty.";
	}
};



//default constructor , do nothing
Deck::Deck(){};

//copy constructor 
Deck::Deck(const Deck& d) {
    
    for(int i = 0; i<(d).size(); i++){
       
        (*this).push_back(d[i]);
    }  
    
};

//returns top card of the deck 
Card* Deck::draw() {
    if ((*this).empty()){
        throw DeckisEmpty();
    }
    else{
        Card* card = (*this).back();
        (*this).pop_back();
        return card;
    }
};

//add card to the deck 
void Deck::add(Card* c){
    (*this).push_back(c);
};

//shuffles the deck using defaut function
void Deck::shuffle(){
    std::random_shuffle(std::begin( (*this) ), std::end( (*this) ));
};

//insertion operator 
ostream& operator<<(ostream& out, const Deck& d) {
	
	for (int i =0;i<d.size();i++){
		d[i]->print(out);
	}
	return out;
};


