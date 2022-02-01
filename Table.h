#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "CardFactory.h"
#include <iostream>
#include <fstream>
#include <string>

class Table {
public:
	vector<Player> players;
	Deck deck;
	DiscardPile discard;
	TradeArea ta;
	

public:
	Table(string& name1, string& name2);
    Table(istream&, CardFactory*);
	bool win(string&);
    void printHand(bool);
	friend ostream & operator << (ostream &, Table);
	void addToDiscard(int, int);
	void print(ostream&);
	
};

//returns wether or not the player in winner or not
bool Table::win(string & name)
{
	//If there is no player, returns the player in the lead.
	if (name == players[0].getName()){
		if (deck.empty() && players[0].getNumCoins() > players[1].getNumCoins()){
			return true ;
		}
		else{
			return false;
		}

	}
	else if (name == players[1].getName()){
		if (deck.empty() && players[1].getNumCoins() > players[0].getNumCoins()){
			return true;
		}
		else{
			return false;
		}

	}
	else{
		return false;
	}
	
}

//constructor 
Table::Table(string &name1,string &name2){

	//CREATING THE PLAYERS 
	Player player1(name1);
	Player player2(name2);
	players.push_back(player1);
	players.push_back(player2);

	//CREATING THE DECK

	CardFactory cf;
	deck = (cf).getDeck();
	
	//ADDING 5 CARDS TO THE HAND OF EACH PLAYER 
	for (int i=0;i<5;i++){
		players[0]+= deck.draw();
		players[1]+= deck.draw();
	}
	cout<<"Each player received 5 cards."<<endl;

	//DISPLAYING THE TO CARD OF EACH PLAYER
	cout<<players[0].getName()<< " ";
	players[0].printHand(cout,true);
	cout<<endl;
	cout<<players[1].getName()<< " ";
	players[1].printHand(cout,true);
	cout<<endl;

}

//constructor from istream
Table::Table(istream & in, CardFactory* cf){

	string test;	
	//ignoring the title line
	getline(in,test, '\n');
	Player *player1 = new Player(in, cf);
	//ignoring the empty line
	getline(in,test, '\n');
	Player *player2 = new Player(in, cf);

	//adding players to the vector of players 
	players.push_back(*player1);
	players.push_back(*player2);

	//ignroing next line 
	getline(in,test, '\n');
	getline(in,test, '\n');
	
	getline(in,test, '\n');
	for (int i=0;i<test.size();i++){
		deck.push_back(cf->getCard(test[i]));
	}
	
	//ignroing next line 
	getline(in,test, '\n');
	getline(in,test, '\n');

	if (test!="The discard pile is empty."){
		for (int i=0;i<test.size();i++){
			discard+=(cf->getCard(test[i]));
		}
	}

	//ignoring next line 
	getline(in,test, '\n');
	getline(in,test, '\n');
	if (test!="The trade area is empty"){
		for (int i=0;i<test.size();i++){
			ta+=(cf->getCard(test[i]));
		}
	}

};


void Table::printHand(bool b){
	players[0].printHand(cout,b);
	players[1].printHand(cout,b);
}

//****************************************
//Format to save a game is the following
// ----PLAYERS---- 
// Adrien
// 0
// ssCsCb
// Empty chain.
// Empty chain.
// Empty chain.

// Hamidou
// 0
// BCsGC
// Empty chain.
// Empty chain.
// Empty chain.

// ----DECK----
// CRGBBgGSCsRCBBCCCSSbCBsSCRGCBSBbSgGBBBGRGbRBgBBsGGsGsgSGCCsBbBSSBGCSRBCSbSsRsbbGRSBgbbSBgGCSS
// ----DISCARD PILE----
// The discard pile is empty.
// ----TRADE AREA----
// The trade area is empty

ostream& operator<<(ostream& out,Table t){
	out<<"----PLAYERS---- "<<endl;
	out<<t.players[0];
	out<<endl;
	out<<t.players[1];
	out<<endl;
	out<<"----DECK----"<<endl;
	out<<t.deck;
	out<<endl;
	out<<"----DISCARD PILE----"<<endl;
	out<<t.discard;
	out<<endl;
	out<<"----TRADE AREA----"<<endl;
	out<<t.ta;
	return out;
}

//print the table 
void Table::print(ostream& out){
	out<<"----PLAYERS---- "<<endl;
	out<<players[0].name<< " "<<players[0].numCoins<<" coins."<<endl;
	out<<players[1].name<< " "<<players[1].numCoins<<" coins."<<endl;
	out<<"----DISCARD PILE----"<<endl;
	discard.print(out);
	cout<<endl;

	out<<"----TRADE AREA----"<<endl;
	ta.print(out);

}

/*
 * Take a card from the player's hand and add it to the discard pile
 * parameter (int) player : player index from whom to take the card
 * parameter (int) card_pos : card to be taken out position in player's hand
 */
void Table::addToDiscard(int player, int card_pos){
	discard += players[player].handOut(card_pos);
}