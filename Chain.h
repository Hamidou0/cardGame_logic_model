//#pragma once
#include <iostream>
#include "Card.h"
#include <vector>
#include "CardFactory.h"

template <class T> class Chain : public vector<T*>{
    //type of the chain (blac,Blue, soy, ...)
    string type;
    public:
        Chain<T>& operator+=(T* card); // add a card to the chain and throws an excepyion if the type is different
        int sell(); //count the number of cards in the chain so far and returns the amount of coins associated to this number (Cards::getCArdsPerCoin)
        friend ostream& operator << (ostream &, Chain<T>); //friend funcrion to print the chain
        //Chain(istream&, const CardFactory* ); // constructor 
        //Chain(); //default constructor 
        void print(ostream&); //print the chain
        void printForFile(ostream& out);
        friend ostream& operator<<(ostream &out,Chain<T> &chain);

};


//the exception for when a card of the wrong type is added to this chain
class IllegalType : public exception
{
	virtual const char* what() const throw()
	{
		return "Wrong card for this type of chain";
	}
};


template<class T>

//sells the chain and return the coin value of it 
int Chain<T>::sell(){
    if ((*this).size()==0){
        return 0;
    }
    else{
        for (int cns = 4; cns > 0; cns--) {
            if ((*this).size() >= (*this).front()->getCardsPerCoin(cns)) {
                (*this).clear();
                return cns;
            }
        }
    }
    (*this).clear();
	return 0;
}

//add a card to the chain
template <class T> Chain<T>& Chain<T>::operator+=(T* card){
    if (!(*this).empty()){
        if (card->getName() != (*this).front()->getName()){
            throw new IllegalType();
        }
        else{
            (*this).push_back(card);
        }
    }
    else{
        (*this).push_back(card);
    }
    return (*this);
}

//insertion operator 
template <class T> ostream& operator<<(ostream &out,Chain<T> &chain){
    cout<<"in operator << of chain"<<endl;
    if (chain->size()>0){
        for (int i =0;i<chain->size();i++){
            //it will use the insertion operator of the card and return its first character 
            chain[i].print(out);
        }
        
    }
	return out;   
}

//print the chain 
template <class T> void Chain<T>::print(ostream& out){
    
    if ((*this).empty()){
        out<<"Empty chain.";
    }
    else{
        out<<(*this)[0]->getName()<< " : ";
        for (int i=0;i<(*this).size();i++){
            (*this)[i]->print(out);
            out<< " ";
        }
        
    } 
    out<<endl;   
}

//used to print the chain as a single line, cmpressed version of print defined above, used for insertion operator 
template <class T> void Chain<T>::printForFile(ostream& out){
    
    if ((*this).empty()){
        out<<"Empty";
    }
    else{
        for (int i=0;i<(*this).size();i++){
            (*this)[i]->print(out);
        } 
    } 
    out<<endl;   
}