/* -----------------------------------------------------------------------------
 player.h
 Backjack
 Created by Nicholas Wereszczak
 Date: 12/8/18
 -----------------------------------------------------------------------------*/

#pragma once

#include "deck.h"

typedef enum {UNKNOWN, IN, BUST, BLACKJACK} StatusT;  // enum for STATUS

class Dealer;

// ----------------------------------------------------------------------------
class Player {
protected:
    std::vector<Card*> hand;
    int score;  // sum of all cards
    const std::string name;
    bool soft;  // if Ace card is currently being used as an 11 (true)
    StatusT status;
    static int gameOverCnt;

public:
    Player(std::string n);
    ~Player() = default;

    void print( std::ostream& out );     // prints player info

    // functions
    void updateStatus();
    int addToHand(Card *c);
    void updateScore();
    void turn(Dealer*);
    std::string formatHand();

    std::string getName() { return name; };
    StatusT getStatus() { return status; };
    int getScore() { return score; };
};

// ----------------------------------------------------------------------------
class Dealer : Player {
private:
    Deck *d;
    std::vector<Player*> players;

public:
    Dealer(std::string n="Dealer", uint8_t decks=4);
    ~Dealer();

    void hit(Player*);    // ask the dealer for a card
    void stand();   // take no card and pass
    void shuffle();
    void deal();
    void winner();
    void addPlayer(std::string);
    void turn();

    std::vector<Player*>& getPlayers() { return players; };
    Deck* deck() { return d; };
};

// ----------------------------------------------------------------------------
// inline operator
inline std::ostream& operator << ( std::ostream& out, Player& p ) {
	p.print(out);
	return out;
}