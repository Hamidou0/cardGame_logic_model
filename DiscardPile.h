#pragma once
#include <vector>
#include "Card.h"

using namespace std;

class DiscardPile{
	
	public:
		vector<Card*> dpile;
		DiscardPile() = default;
		DiscardPile& operator+=(Card*);
		Card* top() ;
		Card* pickUp();
		void print(std::ostream& );
		int size();
		friend ostream& operator<< (std::ostream & , const DiscardPile &);

};

//return the size of the discard pile
int DiscardPile::size(){
	return dpile.size();
}

//add card to the discard pile
DiscardPile& DiscardPile::operator+=(Card* c)
{
	dpile.push_back(c);
	return *this;
}

//returns top card of the discard pile
Card* DiscardPile::top()
{
	return dpile.back();
}

//remove and return top card of the pile
Card* DiscardPile::pickUp()
{
	Card * c = dpile.back();
	dpile.pop_back();
	return c;
}

//insertion operator 
std::ostream& operator<< (std::ostream & os, DiscardPile & dp)
{
	if (dp.size() <= 0) {
		os<<"The discard pile is empty.";
		return os;
	}
	else {
		
		for (Card* card : dp.dpile) {
			card->print(os);
		}
		return os;
	}
}

//print the discard pile 
void DiscardPile::print(std::ostream & os)
{
	if (dpile.size()==0){
		os<<"The discard pile is empty."<<endl;
	}
	else{
		for (Card* card : dpile) {
		os << card->getName();
		os<<endl;
	}
	os<<endl;

	}
	
}