/* -----------------------------------------------------------------------------
 deck.cpp
 Blackjack
 Created by Nicholas Wereszczak
 Date: 12/8/18
----------------------------------------------------------------------------- */

#include <random>
#include "deck.h"

// ----------------------------------------------------------------------------
Deck::Deck( uint8_t decks ) : deckCount(decks)
{
    // init the number of decks you need
    createDeck();
}

// ----------------------------------------------------------------------------
Deck::~Deck()
{
    // be sure to clean up all the allocated cards
    for( Card *c : cards )
    {
        cards.pop_back();
        delete c;
    }
}

// ----------------------------------------------------------------------------
void Deck::createDeck()
{
    // create the number of decks needed
    for( int x=0; x<deckCount; x++ )
    {
        std::vector<Card*> d;
        createStdDeck(d);
        cards.insert(cards.end(), d.begin(), d.end());  // merge the vectors/decks
    }
}

// ----------------------------------------------------------------------------
void Deck::createStdDeck( std::vector<Card*> &d )
{
    // Create a standard 52 card deck
    //      4 of each rank
    //      ignore suit and color

    // 13 X 4 = 52
    for( const auto& n : Card::types )
    {
        for( int x=0; x<4; x++ )
        {
            Card *c = new Card(n.first, n.second);
            d.push_back(c);
        }
    }
}

// ----------------------------------------------------------------------------
void Deck::shuffle()
{
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

// ----------------------------------------------------------------------------
// prints to certain stream
// ----------------------------------------------------------------------------
void Deck::print( std::ostream& out ) {
    for( Card *c : cards )
    {
        c->print(out);
        out << " ";
    }
    out << std::endl;
}

// ----------------------------------------------------------------------------
Card* Deck::draw() 
{ 
    Card *c = cards.back();
    cards.pop_back();
    return c;
}

// ----------------------------------------------------------------------------