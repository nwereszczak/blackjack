/* -----------------------------------------------------------------------------
 card.h
 Backjack
 Created by Nicholas Wereszczak
 Date: 12/8/18
 -----------------------------------------------------------------------------*/

#pragma once

#include <cstdint>
#include <iostream>
#include <unordered_map>

//const uint8_t values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
//const char ranks[] = {"-A23456789TJQK"};
#define BLACKJACK_SCORE 21

// ----------------------------------------------------------------------------
class Card {
private:
    std::string rank;
    int value;  // can change (only for Aces though)
    // suit & color are also a part of a standard "Card", but are not needed in this game

public:
    static std::unordered_map<std::string, int> types;

    Card(std::string r, int v) : rank(r), value(v) {};
    ~Card() = default;

    void print( std::ostream& out );     // prints card

    // functions
    std::string getRank() { return rank; };
    int getValue() { return value; };
    void setValue(int v) { value = v; };
};

// inline operator
inline std::ostream& operator << ( std::ostream& out, Card& c ) {
	c.print( out );
	return out;
}

// ----------------------------------------------------------------------------