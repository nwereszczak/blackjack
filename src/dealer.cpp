/* -----------------------------------------------------------------------------
 dealer.cpp
 Blackjack
 Created by Nicholas Wereszczak
 Date: 12/8/18
----------------------------------------------------------------------------- */

#include "player.h"

// ----------------------------------------------------------------------------
//                                  Dealer
// ----------------------------------------------------------------------------
Dealer::Dealer( std::string n, uint8_t decks ) : Player(n), d(nullptr)
{
    // create and use the deck
    d = new Deck(decks);   // default is 4 decks
    players.push_back(this);    // add yourself to the list
}

// ----------------------------------------------------------------------------
Dealer::~Dealer()
{
    if( d != nullptr )
        delete d;
    d = nullptr;

    for( Player *p : players )
    {
        delete p;
    }
    players.clear();
}

// ----------------------------------------------------------------------------
void Dealer::shuffle()
{
    d->shuffle();
}

/* ----------------------------------------------------------------------------
Players are each dealt two cards, face up or down depending on the casino and 
the table at which you sit. In the U.S., the dealer is also dealt two cards, 
normally one up (exposed) and one down (hidden).
 ---------------------------------------------------------------------------- */
void Dealer::deal()
{
    int cnt = 0;
    for( Player* p : players )
    {
        while(cnt !=2)  // need two cards in hand
        {
            cnt = p->addToHand( d->draw() );
        }
        cnt = 0;
    }
}

// ----------------------------------------------------------------------------
void Dealer::addPlayer(std::string name)
{
    players.insert( players.begin(), new Player(name) );
}

// ----------------------------------------------------------------------------
void Dealer::turn()
{
    std::cout << "Dealer's Turn" << std::endl;
    // The dealer hand will not be completed if all players have either busted or received blackjacks.
    //  - that variable to check will be set in Player::status()
    if( gameOverCnt == players.size()-1 )
    {
        std::cout << "All other players have BUST or BLACKJACK - GAMEOVER" << std::endl;
        std::cout << "Turn Over" << std::endl;
        std::cout << std::endl;
        return;
    }

    // The dealer then reveals the hidden card and must hit until the cards total 17 or more points. 
    while( score < 17 )
    {
        hit(this);
        print(std::cout);

        if( status==BUST || status==BLACKJACK ) 
            break;
    }

    std::cout << "Turn Over" << std::endl;
    std::cout << std::endl;
    
    // not implementing
    // (At most tables the dealer also hits on a "soft" 17, i.e. a hand containing an ace and one or more other cards totaling six.)
}

// ----------------------------------------------------------------------------
void Dealer::hit( Player* p )
{
    p->addToHand( d->draw() );
    p->updateScore();
}

// ----------------------------------------------------------------------------
void Dealer::stand()
{
    // do nothing
}

// ----------------------------------------------------------------------------
void Dealer::winner()
{
    if( status == BLACKJACK )
    {
        std::cout << "The Dealer wins :(" << std::endl;
        return;
    }
        
    // tell them which players won
    for (auto it = players.begin(); it != players.end()-1; it++)
    {
        Player *p = *it;
        switch( p->getStatus() ) {
            case BLACKJACK:
                std::cout << p->getName() << " is a winner!" << std::endl;
                continue;
            case BUST:
                std::cout << p->getName() << " loses!" << std::endl;
                continue;
        }

        if( p->getStatus() == IN )
        {
            if( status == BUST )
            {
                std::cout << p->getName() << " is a winner!" << std::endl;
                continue;
            }

            if( p->getScore() > score )
                std::cout << p->getName() << " is a winner!" << std::endl;
            else if( p->getScore() < score )
                std::cout << p->getName() << " loses!" << std::endl;
            else if( p->getScore() == score )
                std::cout << p->getName() << " matches Dealer.  It is a \"push\".  No bets lost." << std::endl;
        }
    }
}

// ----------------------------------------------------------------------------