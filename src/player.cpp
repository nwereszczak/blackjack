/* -----------------------------------------------------------------------------
 player.cpp
 Blackjack
 Created by Nicholas Wereszczak
 Date: 12/8/18
----------------------------------------------------------------------------- */

#include "player.h"

const std::string p_status[] = {"Unknown", "In", "Bust", "Blackjack"};
int Player::gameOverCnt = 0;

// ----------------------------------------------------------------------------
//                                  Player
// ----------------------------------------------------------------------------
Player::Player( std::string n ) : name(n)
{
    score = 0;
    soft = false;
    status = UNKNOWN;
}

// ----------------------------------------------------------------------------
int Player::addToHand( Card *c )
{
    hand.push_back(c);
    updateScore();
    return hand.size();
}

// ----------------------------------------------------------------------------
void Player::updateScore()
{
    int tmpScore = 0;
    for( Card* c : hand )
    {
        if( c->getRank() == "A" )
        {
            if( tmpScore + 11 > BLACKJACK_SCORE )
            {
                c->setValue(1);
                soft = false;   // not soft since it has to be a '1' otherwise you bust
            }
            else {
                c->setValue(11);
                soft = true;
            }
        }
        tmpScore += c->getValue();
    }
    score = tmpScore;

    // update the status based on score
    updateStatus();
}

// ----------------------------------------------------------------------------
void Player::updateStatus()
{
    if( score < BLACKJACK_SCORE )
    {
        status = IN;
    }
    else if( score == BLACKJACK_SCORE )
    {
        status = BLACKJACK;
        gameOverCnt++;
    }
    else if( score > BLACKJACK_SCORE )
    {
        status = BUST;
        gameOverCnt++;
    }
}

// ----------------------------------------------------------------------------
void Player::turn(Dealer *dealer)
{
    std::string c;
    std::cout << "Player " << name << "'s Turn" << std::endl;

    for(;;) // loop until each playter finishes (wins or busts or stands)
    {
        std::cout << "Hit or stand? (H/S): ";
        std::cin >> c;
        
        if( c == "H" || c == "h" )
        {
            dealer->hit(this);
        }
        else {   // else they give up there turn
            dealer->stand();
            break;
        }

        print(std::cout);

        if( status == BUST || status == BLACKJACK ) 
            break;
    }
    std::cout << "Turn Over" << std::endl;
    std::cout << std::endl;
}

// ----------------------------------------------------------------------------
void Player::print( std::ostream& out )
{
    out << "--------------------------------------------------------------------------------------------" << std::endl;
    out << "\t"<< name << "\t\t|\t" << formatHand() << "\t\t|\t" << score << "\t\t|\t" << p_status[status] << std::endl;  
}

// ----------------------------------------------------------------------------
std::string Player::formatHand()
{
    std::string s("(");
    for( Card *c : hand )
    {
        s += c->getRank();
        s += ", ";
    }
    s = s.substr(0, s.size()-2);
    s += ")";
    return s;
}

// ----------------------------------------------------------------------------
