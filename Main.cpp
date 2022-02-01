#include <iostream>
#include <string>
#include <algorithm>
#include "table.h"

using namespace std;

static void saveGame(Table table) {
	ofstream outputFile("game.txt");
    outputFile<<table;
    cout<<"GAME SAVED IN : game.txt !"<<endl;
}

int main(){ 
    //asking if the user continues a game from file or start a new game
    
    int answer;
    string name1,name2;
    CardFactory *cf = CardFactory::getFactory();
    Table *table;

    //aesthetic separator 
    string dashes = "\n---------------- :::::::_________:::::::: ---------------\n";
    std::vector<std::string> beans;
    beans.push_back("black");
    beans.push_back("Blue");
    beans.push_back("Chili");
    beans.push_back("garden");
    beans.push_back("Green");
    beans.push_back("Red");
    beans.push_back("soy");
    beans.push_back("Stink");

    cout<<"Welcome to Bonhanzha ! "<<endl;
    cout<<"Tapez 1 pour commencer un nouveau jeux."<<endl<<"Tapez 2 pour continuer une partie en cours."<<endl<<"Tapez 3 pour quitter."<<endl<<"Your choice : ";
    cin>>answer;

    //handling incorrect entry 
    while(cin.fail() ||(answer != 1 && answer != 2 && answer != 3) ){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        cout<<"Tapez 1 pour commencer un nouveau jeux."<<endl<<"Tapez 2 pour continuer une partie en cours."<<endl<<"Tapez 3 pour quitter."<<endl<<"Your choice : ";
        cin>> answer;
    }
    
    //if the user wants ot leave the game 
    if (answer == 3){
        cout<<"Thank you ! Come back soon..."<<endl;
        return 1;
    }

    //loading from file 
    if (answer == 2) {
        cout<<"Loading game from file."<<endl;;
        ifstream inputFile("game.txt");
        if (inputFile.is_open()) {
            table = new Table(inputFile, cf);
        }
    }
   
    

    //if the user wants to start a new game, we initialise the players with the new names 
    if (answer == 1 ){
        cout<<"Starting a new game.\n "; 
        cout<<"Enter the name of first player : ";
        cin>>name1;
        cout<<"Enter the name of second player : ";
        cin>>name2;

        table = new Table(name1,name2);
    }else{}
       
        //The table is ready, we can start the game 

        //while there are still cards in the deck 
        while(!table->deck.empty()){
           
            string answer ;

            //for each player
            for (int i=0;i<table->players.size();i++){
                table->print(cout);
        
                cout<<dashes<<endl;
                //print some informations about the player
                cout << table->players[i].getName() << " turn:"<<endl;
                table->players[i].printHand(cout,true);
                cout << table->players[i].getName() << " chains are: "<<endl;
                table->players[i].printChains();
                cout<<dashes<<endl;
                int m_choice;
                string option;
                //while the player wants to add or sell cards 
                do{
                    cout << "Do you want to add a card to a chain or sell a chain?(add/sell) || type ' save ' to save and exit the game  : ";
                    cin >> option;
                    while(option != "add" && option != "sell" && option != "save"){
                        cout<<"Please answer either ' add 'or ' sell ' : ";
                        cin>>option;
                    }
                    if (option=="save"){
                        saveGame(*table);
                        return 0;
                    }
                    if(option.compare("add") == 0){
                        //chain choice
                        //the user cselect the chain, and we handle invalid entries 
                        if (table->players[i].maxNumChain==3){
                            cout << "Which chain ? (1,2,3) : ";
                            cin >> m_choice;
                            while(cin.fail() ||(m_choice != 1 && m_choice != 2 && m_choice != 3) ){
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                cout<<"Please answer either 1,  2  or  3 : ";
                                cin>> m_choice;
                            }           
                        }
                        else{
                            cout << "Which chain ? (1,2) : ";
                            cin >> m_choice;
                            while(cin.fail()|| (m_choice != 1 && m_choice != 2)){
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                cout<<"Please answer either 1 or 2 : ";
                                cin>> m_choice;
                            }
                        }
                        //catch the wrong type exception from the Chain class
                        try{
                            table->players[i].playChain(m_choice);
                            
                            cout << table->players[i].getName() << " chains are : "<<endl;

                            table->players[i].printChains();
                            cout << "Do you want to sell or add again? ( y/n) : ";
                            cin>>answer;
                            while(answer != "y" && answer != "n"){
                                cout<<"Please answer either ' y ' for Yes or ' n ' for No : ";
                                cin>>answer;
                            }
                        }
                        catch(int e){
                            cout << "Wrong card type"<<endl;
                            answer="y";
                        }
                    }
                    else if (option.compare("sell") == 0){
                        //chain choice
                        cout<<"Selling: "<<table->players[i].maxNumChain<<" chains."<<endl;
                        //the user cselect the chain, and we handle invalid entries 
                        if (table->players[i].maxNumChain==3){
                            cout << "Which chain ? (1,2,3) : ";
                            cin >> m_choice;
                            while(cin.fail() ||(m_choice != 1 && m_choice != 2 && m_choice != 3) ){
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                cout<<"Please answer either 1,  2  or  3 : ";
                                cin>> m_choice;
                            }           
                        }
                        else{
                            cout << "Which chain ? (1,2) : ";
                            cin >> m_choice;
                            while(cin.fail()|| (m_choice != 1 && m_choice != 2)){
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                cout<<"Please answer either 1 or 2 : ";
                                cin>> m_choice;
                            }
                        }
                       
                        //chain if the chain isnt empty
                        if( (table->players[i]).chains[m_choice-1].size() == 0 ){
                           
                            cout << "That chain is empty." << endl;
                            answer = "n";
                        }else{
                            //sell the chain and add the coins to player
                            
                            cout<<table->players[i].getName()<<" new chains are:"<<endl;
                            table->players[i] += (table->players[i]).chains[m_choice-1].sell();
                            table->players[i].printChains();
                            cout << table->players[i].getName() << "'s coins: "<<table->players[i].getNumCoins()<<endl;
                            cout << "Do you want to sell or add again? ( y/n) : ";
                            cin>>answer;
                            while(answer != "y" && answer != "n"){
                                cout<<"Please answer either ' y ' for Yes or ' n ' for No"<<endl;
                                cin>>answer;
                            }
                        }
                    }else{}
                }while(answer == "y");

                cout<<dashes<<endl;
                cout << table->players[i].getName() << "'s hand"<<endl;
                table->players[i].printHand(cout,true);
                cout << "Do you want to place a card in the discard pile? (y/n) : ";

                cin>>answer;
                while(answer != "y" && answer != "n"){
                    cout<<"Please answer either ' y ' for Yes or ' n ' for No"<<endl;
                    cin>>answer;
                }
                if(answer == "y"){
                    //card position choice
                        cout << "Which position from 0 to "<<(table->players[i].hand->size()-1) <<", 0 being the last card in your hand : ";
                        cin >> m_choice;
                        table->addToDiscard(i, m_choice);
                        cout << table->players[i].getName() << "'s hand"<<endl;
                        table->players[i].printHand(cout,true);
                }
                cout<<dashes<<endl;
                cout << "3 cards from the deck have been drawn and put in the trade area"<<endl;
                for(int s = 0; s < 3; s++){
                    if (table->deck.size() != 0){ 
                        table->ta += table->deck.draw();
                    }
                }
                cout << "Cards have been drawn from the deck"<<endl;
                unsigned char go_on = 1;
                //check if the card drwan from the deck is legal
                while(go_on == 1){
                    
                    if(table->discard.size() != 0 && table->ta.legal(table->discard.top())){
                        table->ta += table->discard.pickUp();
                    }else{
                        go_on = 0;
                    }
                }

                //now entering the trade area 
                cout<<dashes<<endl;
                cout << "This is the trade area"<<endl;
                table->ta.print(cout);
                cout<< "This is "<<table->players[i].getName()<<"'s chains"<<endl;;
                table->players[i].printChains();
                cout << "Do you want to chain a card from the trading area? (y/n) : ";
                cin>>answer;
                while(answer != "y" && answer != "n"){
                    cout<<"Please answer either ' y ' for Yes or ' n ' for No : ";
                    cin>>answer;
                }

                //assking the user what card from the trade area they want to pick up 
                while(answer == "y"){
                        
                        while(answer == "y"){
                            cout << "Which card do you want to take?"<<endl<<"Type the card full name"<<endl;
                            cout << " -b = black\n -B = Blue\n -C = Chili\n -g = garden\n -G = Green\n -R = red\n -s = soy\n -S = Stink\nYour Choice : ";
                            cin >> option;
                            while(find(beans.begin(),beans.end(), option) == beans.end()){
                                cout<<"Invalide beans, please note that the bean's names are case sensitive"<<endl;
                                cout<<dashes<<"\nDo you want to choose a card from the trading area (y/n)?"<<endl;
                                cin>>answer;
                                while(answer != "y" && answer != "n"){
                                    cout<<"Please answer either ' y ' for Yes or ' n ' for No : ";
                                    cin>>answer;
                                }
                                if(answer == "y"){
                                    cout << "Which card do you want to take?"<<endl<<"Type the card full name : ";
                                    cin >> option;
                                }
                            }
                            
                            cout<<"The player selected :"<<option<<endl;
                            if(table->players[i].legal(option)){

                                //if the card is legal we add it to the chain, or an empty chain is 
                                try{
                                    //the user select the chain, and we handle invalid entries 
                                    if (table->players[i].maxNumChain==3){
                                        cout << "Which chain ? (1,2,3) : ";
                                        cin >> m_choice;
                                        while(cin.fail() ||(m_choice != 1 && m_choice != 2 && m_choice != 3) ){
                                            std::cin.clear();
                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                            cout<<"Please answer either 1,  2  or  3 : ";
                                            cin>> m_choice;
                                        }           
                                    }
                                    else{
                                        cout << "Which chain ? (1,2) : ";
                                        cin >> m_choice;
                                        while(cin.fail()|| (m_choice != 1 && m_choice != 2)){
                                            std::cin.clear();
                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                            cout<<"Please answer either 1 or 2 : ";
                                            cin>> m_choice;
                                        }
                                    }
                                    bool go = true;
                                    while (!table->players[i].legal(m_choice-1, option) && go)
                                    {
                                        cout<<"You can not put that card in that chain try another one."<<endl;
                                        cout << "Do you want to try another chain? ( y/n) : ";
                                        cin>>answer;
                                        while(answer != "y" && answer != "n"){
                                            cout<<"Please answer either ' y ' for Yes or ' n ' for No : ";
                                            cin>>answer;
                                        }
                                        //the user cselect the chian, and we handle invalid entries 
                                        if(answer == "y"){
                                            if (table->players[i].maxNumChain==3){
                                                cout << "Which chain ? (1,2,3) : ";
                                                cin >> m_choice;
                                                while(cin.fail() ||(m_choice != 1 && m_choice != 2 && m_choice != 3) ){
                                                    std::cin.clear();
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                                    cout<<"Please answer either 1,  2  or  3 : ";
                                                    cin>> m_choice;
                                                }           
                                            }
                                            else{
                                                cout << "Which chain ? (1,2) : ";
                                                cin >> m_choice;
                                                while(cin.fail()|| (m_choice != 1 && m_choice != 2)){
                                                    std::cin.clear();
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                                    cout<<"Please answer either 1 or 2 : ";
                                                    cin>> m_choice;
                                                }
                                            }
                                        }
                                        else{
                                            go = false;
                                        }
                                    }
                                    if(answer == "y"){
                                        Card* temp_card = table->ta.trade(option);
                                        table->players[i].playChain(m_choice,temp_card);
                                        answer = "n";
                                    }
                                }catch(...){
                                    cout<<"No such card in the trading area"<<endl;
                                    cout << "Want to choose another one? ( y/n ) : ";
                                    cin>>answer;
                                    while(answer != "y" && answer != "n"){
                                        cout<<"Please answer either ' y ' for Yes or ' n ' for No : ";
                                        cin>>answer;
                                    }                                    
                                }
                            }else{
                                cout << "You can not chain that bean."<< endl;
                                cout << "Want to choose another one? ( y/n ) : ";
                                cin>>answer;
                                while(answer != "y" && answer != "n"){
                                    cout<<"Please answer either ' y ' for Yes or ' n ' for No : ";
                                    cin>>answer;
                                }
                            }
                        }
                    
                    //after the trading area, asking the user if they want to sell a chain
                    cout<<dashes<<endl;
                    table->players[i].printChains();
                    cout << "Do you want to sell a chain? ( y/n) : ";
                    cin>>answer;
                    while(answer != "y" && answer != "n"){
                        cout<<"Please answer either ' y ' for Yes or ' n ' for No : ";
                        cin>>answer;
                    }

                    while (answer == "y"){
                        //chain choice
                        //the user cselect the chain, and we handle invalid entries 
                        if (table->players[i].maxNumChain==3){
                            cout << "Which chain ? (1,2,3) : ";
                            cin >> m_choice;
                            while(cin.fail() ||(m_choice != 1 && m_choice != 2 && m_choice != 3) ){
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                cout<<"Please answer either 1,  2  or  3 : ";
                                cin>> m_choice;
                            }           
                            }
                        else{
                            cout << "Which chain ? (1,2) : ";
                            cin >> m_choice;
                            while(cin.fail()|| (m_choice != 1 && m_choice != 2)){
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                                cout<<"Please answer either 1 or 2 : ";
                                cin>> m_choice;
                            }
                        }
                        //chain if the chain isnt empty
                        if( (table->players[i]).chains[m_choice-1].size() == 0 ){
                            cout << "That chain is empty." << endl;
                        }else{
                            //sell the chain and add the coins to player
                            cout<<"Selling :"<<(table->players[i]).getName()<<endl;
                            table->players[i] += (table->players[i]).chains[m_choice-1].sell();
                            table->players[i].printChains();
                            cout << table->players[i].getName() << "'s coins: "<<table->players[i].getNumCoins()<<endl;
                        }
                        cout << "Do you want to sell again? ( y/n) : ";
                        cin>>answer;
                        while(answer != "y" && answer != "n"){
                            cout<<"Please answer either ' y ' for Yes or ' n ' for No : ";
                            cin>>answer;
                        }
                    }
                    cout << "Do you want to chain a card from the trading area? (y/n) : ";
                    cin>>answer;
                    while(answer != "y" && answer != "n"){
                        cout<<"Please answer either ' y ' for Yes or ' n ' for No : ";
                        cin>>answer;
                    }
                    if(answer == "y"){
                        cout<<dashes<<endl;
                        cout << "This is the trade area :"<<endl;
                        table->ta.print(cout);
                    }
                }

               int num_card = 0;
                for(int s = 0; s < 2; s++){
                    if (table->deck.size() != 0) {
                        table->players[i] += table->deck.draw();
                        num_card++;
                    }
                }
                cout << "End of your turn, You've drawn "<<num_card<<" cards from the deck"<<endl;
                cout<<dashes<<endl;
            }
        }

        //when the deck is empty, we display th winner and their coins 
        cout<<dashes<<"\nThe deck is empty! End of the Game!"<<endl;

        //if both users have the same amount of coins 
        if(table->players[0].getNumCoins() == table->players[0].getNumCoins()){
            cout<<"It's a tie!"<<endl;
            cout<<table->players[0].getName()<<"' coins: "<<table->players[0].getNumCoins()<<endl;
            cout<<table->players[1].getName()<<"' coins: "<<table->players[1].getNumCoins()<<endl;
        }else{

            //if not they we check the winners 
            string winner_ = table->players[0].getName();
            if(table->win(winner_)){
                cout<<table->players[0].getName()<<" won, congratulation!"<<endl;
                cout<<table->players[0].getName()<<"' coins: "<<table->players[0].getNumCoins()<<endl;
                cout<<table->players[1].getName()<<"' coins: "<<table->players[1].getNumCoins()<<endl;
            }else{
                cout<<table->players[1].getName()<<" won, congratulation!"<<endl;
                cout<<table->players[1].getName()<<"' coins: "<<table->players[1].getNumCoins()<<endl;
                cout<<table->players[0].getName()<<"' coins: "<<table->players[0].getNumCoins()<<endl;
            }
        }
        
                
    return 1;
}