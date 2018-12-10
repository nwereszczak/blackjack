/* -----------------------------------------------------------------------------
 deck.h
 Backjack
 Created by Nicholas Wereszczak
 Date: 12/8/18
 -----------------------------------------------------------------------------*/

#pragma once

#include <algorithm>
#include <vector>
#include <chrono>

#include "card.h"

// ----------------------------------------------------------------------------
class Deck {
private:
    std::vector<Card*> cards;
    const uint8_t deckCount;

public:
    Deck(uint8_t decks);
    ~Deck();

    void print( std::ostream& out );     // prints deck

    // functions
    void createDeck();
    void createStdDeck(std::vector<Card*> &);
    void shuffle();
    Card* draw();
};

// inline operator
inline std::ostream& operator << ( std::ostream& out, Deck& d ) {
	d.print(out);
	return out;
}

// ----------------------------------------------------------------------------