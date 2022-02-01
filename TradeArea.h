#include "Card.h"
#include <string>
#include "CardFactory.h"
#include <istream>
#include <typeinfo>
#include <list>
#include <stdexcept>
#include <typeinfo>
#include <iterator>

using namespace std;

class TradeArea{
    list<Card*> echange_cards;
	friend class Table; //so that table can manipulate the list of cards directly. used for Table::clearTradeArea()
public:
	TradeArea();
	//TradeArea(istream&, CardFactory*);
	TradeArea& operator+=(Card*);
	bool legal(Card*) const;
    bool legal(string) const;
	Card* trade(string);
	int numCards();
	friend std::ostream& operator<<(ostream&, const TradeArea &);
    bool isEmpty(); //check if the trade area is empty
    void print(ostream&);
};

/*
 * implementation of the cpp file inside
 * the header file
 */

//default constructor 
TradeArea::TradeArea(){
    echange_cards.clear();
}

//add card to the trade area 
TradeArea& TradeArea::operator+=(Card* ca){
    echange_cards.push_back(ca);
    return *this;
}

//check if a card is legal (from card)
bool TradeArea::legal(Card* ca) const{
    for (auto& it : echange_cards) {
        if(ca->getName() == it->getName()){
            return true;
        }
    }
    return false;
}

//check if  card is legal (from string)
bool TradeArea::legal(string ca) const{
    for (auto& it : echange_cards) {
        if(ca == it->getName()){
            return true;
        }
    }
    return false;
}

/*
 * take a card with the same name as the parameter from
 * the trading area and return it as a Card*
 */
Card* TradeArea::trade(string ca){
    Card* reponse;
    list<Card*>::iterator it;
    for (it = echange_cards.begin(); it != echange_cards.end(); ++it) {
        if(ca == (*it)->getName()){
            reponse = *it;
            echange_cards.erase(it);
            return reponse;
        }
    }
    throw domain_error("No such card in the trading area");    
}

//return the number of cards in the trade area 
int TradeArea::numCards(){
    return echange_cards.size();
}

//insertion operator 
std::ostream & operator<<(ostream & out, const TradeArea &tradeArea) {
    if (tradeArea.echange_cards.size()<=0){
        out<<"The trade area is empty"<<endl;
    }
    else{
        for (auto const &i: tradeArea.echange_cards) {
            i->print(out);
        }
    }
	return out;
}

//return wether or not the trade area is empty 
bool TradeArea::isEmpty(){
    return echange_cards.empty();
}

//print the trade area 
void TradeArea::print(ostream& out){
    if (echange_cards.size()<=0){
        out<<"The trade area is empty"<<endl;
    }
    else{

        for (auto const &i: echange_cards) {
            out << i->getName()<<endl;
        }
    }
}