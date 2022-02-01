#pragma once
#include <string.h>
#include <exception>
#include "Chain.h"
#include <iostream>
#include "Hand.h"
#include <vector>

using namespace std;

class Player{
    public:
        string name;
        int numCoins;
        int numChain;
        int maxNumChain;
        Hand *hand;
        Chain<Card> chain1;
        Chain<Card> chain2;
        Chain<Card> chain3;
        vector< Chain<Card> > chains;
       
    

    public:
        Player(std::string);//creates a player with their name
        std::string getName() const; //returns the name of the player
        int getNumCoins(); //returns the number of coins for the player
        Player& operator+=(int); //add coins to the player
        Player& operator+=(Card*); //add cards to the hand of the player
        int getMaxNumChains(); //returns the number of chains the player can have 2 or 3 if they bought a third slot
        int getNumChains(); //returns number of non-null chains
        Card* handOut(int); //returns and delete the card at that position from hand
        Chain<Card>& operator[](int); //return chain in position i
        bool legal(string); //check if a card with the same name exist or empty chain
        bool legal(int, string); //check if a card with the same name exist or empty chain
        void buyThirdChain(); //buys a new chian or return the exception 
        void playChain(int); //get the card on top of the play and put it in one of the chain
        void printHand(std::ostream&,bool); //returns the first card in hand (if bool = false) or the hand of the player (if true)
        void printChains(); //print the chains under a player to the standard output
        friend ostream & operator << (ostream &, Player);
        Player(istream& , CardFactory* );
        void addToChain(int, Card*); // adding the card to a chain 
        void playChain(int chain, Card* card);

};

class NotEnoughCoins : public exception {
    virtual const char* what() const throw()
	{
		return "You do not have enough coins to buy a third chain";
	}

	friend ostream & operator << (ostream & out, NotEnoughCoins e) {
		out << e.what();
		return out;
	}
};

//IMPLEMENTATION OF PLAYER 

//constructor from istream 
Player::Player(istream& in, CardFactory* cf ){
    //cout<<"In player istream constructor"<<endl;
	getline(in,name, '\n');
    in>>numCoins;
	in>>maxNumChain;

    //cout<<"Creating new player : "<<name<<" "<<maxNumChain<< " "<<numCoins<<endl;
	hand = new Hand(in, cf);
    //Now that the hand is ready we an retrive the chains 
    
    Chain<Card> chain1;
    Chain<Card> chain2;
    Chain<Card> chain3;


    chains.push_back(chain1);
    chains.push_back(chain2);
    chains.push_back(chain3);


	char type;
	int size;
	string chain;
	string tmp;
	for (int i = 0; i < 3; i++) {
		in>>chain;
		if (chain.compare("Empty") != 0) {
			type = chain.at(0);
			size = chain.size();
			
			for (int j = 0; j < size; j++) {
				chains[i].push_back(cf->getCard(type));
			}
		}

	}
    string test;	
	//ignoring the space line until the next player
	getline(in,test, '\n');
}
	


//constructor of the player 
Player::Player(std::string playerName){
    name = playerName;
    numCoins=0;
    numChain=0;
    maxNumChain=2;
    hand = new Hand();

    Chain<Card> chain1;
    Chain<Card> chain2;
    Chain<Card> chain3;


    chains.push_back(chain1);
    chains.push_back(chain2);
    chains.push_back(chain3);
    
}

//return the name of the player
std::string Player::getName() const{
    return name;
}

//return the number of points of the player 
int Player::getNumCoins(){
    return numCoins;
}

//add coins to the player 
Player& Player::operator+=(int coins){
    numCoins += coins;
    return (*this);
}
//adding a card to the hand 
Player & Player::operator+=(Card *card)
{
	*hand += card;
	return *this;
}

//get the card on top of the play and put it in one of the chain
void Player::playChain(int chain){

    int chainPos = chain-1;

    //if the chain selcted is empty, we create a new one
    if (chains[chainPos].empty()){
        chains[chainPos].operator+=(hand->play());

    }
    else{
        //cout<<"The chain we want to add is not empty."<<endl;
        //then we check if this is legal
        try {
            chains[chainPos] +=  hand->play();
        }
        catch(exception e){
            cout<<e.what();
        }
    }
    
}

//adding a card to the chain
void Player::playChain(int chain, Card* card){
    chains[chain-1]+=card;
}

//returns the number max of chains a user can have 
int Player::getMaxNumChains(){
    return maxNumChain;
}

//return the number of no-null chains
int Player::getNumChains(){
    return numChain;
}

//return chain in position i
Chain<Card>& Player::operator[](int i) {	
	 if (i < getNumChains()){
         return chains[i];
     }
}

//buys a thord chain for the player and retun exception if not enough coins
void Player::buyThirdChain(){
    if (numCoins>=2){
        numCoins = numCoins -2;
        maxNumChain++;
    }
    else{
        throw NotEnoughCoins();
    }
}
//print the chains under a player to the standard output
void Player::printChains(){

    for ( int x = 0; x < (*this).getMaxNumChains();x++){  
        cout<<x+1<<"_ ";     
        chains[x].print(cout);
    }

    
}

/*
 * Check if a card with the same name is present in one of 
 * the chains or if there's an empty chain
 */
bool Player::legal(string ca) {
    for ( int x = 0; x < getMaxNumChains();x++){
        //if there's an empty chain
        if (chains[x].size() == 0){
            return true;
        } 
        else{
            for (Card* it : chains[x]) {
                if(it->getName() ==  ca){
                    return true;
                }
            }
        }
    }
    return false;
}

/*
 * Check if a card is legal for a specific chain
 */
bool Player::legal(int x, string ca) {
        //if there's an empty chain
        if (chains[x].size() == 0){
            //cout<<"The chain is empty so this is legal."<<endl;
            return true;
        } 
        else{
            for (Card* it : chains[x]) {
                if(it->getName() ==  ca){
                    //cout<<"Found a "<<it->getName()<<" chain ! So legal."<<endl;
                    return true;
                }
            }
        }
    
    return false;
}

void Player::printHand(std::ostream& out,bool b){
    if (b){
        (*hand).print(out);
    }
    else{
        out<<(*hand).top()->getName();
    }
}

Card* Player::handOut(int position){
    Card* temp = (*hand).at(position);
    (*hand).erase((*hand).begin()+position);
    return temp;
}
//name
//coins
//hand
//chain1
//chain2
//chain3

//insertion operator
ostream & operator<<(ostream & out, Player p)
{
    //cout<<"IN PLAYER "<<p.getName()<<endl;
	out << p.getName();
    out<<endl;
    out <<p.getNumCoins();
    out<<endl;
    out <<p.maxNumChain;
    out<<endl;
    out<<(*p.hand);
    out<<endl;
	for (int i = 0; i < p.chains.size(); i++){
        //cout<<"In the for loop"<<endl;
        p.chains[i].printForFile(out);
    }
	return out;


}

//add card to a chain
void Player::addToChain(int chain, Card* card){
    chains[chain] += card;
}
