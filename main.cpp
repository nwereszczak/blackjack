/* -----------------------------------------------------------------------------
 main.cpp
 Backjack
 Created by Nicholas Wereszczak
 Date: 12/8/18
 -----------------------------------------------------------------------------*/

#include "player.h"

// ----------------------------------------------------------------------------
void summary( std::vector<Player*> &players )
{
    using namespace std;    // for ease of use 

    // print out a summary of this round
    //  - each players hand (one face up one face down)
    //  - each players score
    //  - players status (backjack, bust, etc.)

    cout << endl;
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << "\tName\t\t|\t\tHand\t\t|\t\tScore\t\t|\tStatus" << endl;
    for( auto p : players )
    {
        p->print(cout);
    }
    cout << "--------------------------------------------------------------------------------------------" << endl;
    cout << endl;
}

// ----------------------------------------------------------------------------
int main (void)
{
    Player *p = nullptr;

    Dealer *dealer = new Dealer();
    dealer->shuffle();  // tell the dealer to shuffle the deck

    // How many players?  1 for now...
    std::string name;
    std::cout << "What is your name?: ";
    std::cin >> name;
    dealer->addPlayer(name);

    // save the players as a ref 
    std::vector<Player*> &players = dealer->getPlayers();

    // deal the cards out to the players
    std::cout << "Dealing the cards..." << std::endl;
    dealer->deal();
    summary(players);

    // loop over the players (dealer last go )
    // -1 to stop before the dealers turn
    for (auto it = players.begin(); it != players.end()-1; it++)
    {
        p = *it;
        p->turn(dealer);
    }

    // dealers turn
    dealer->turn();

    std::cout << "Final Summary" << std::endl;
    summary(players);

    dealer->winner();
    
    // clean up the Dealer
    delete dealer;

    return 0;
}

// ----------------------------------------------------------------------------
