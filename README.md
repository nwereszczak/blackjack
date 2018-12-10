
# Blackjack

https://en.wikipedia.org/wiki/Blackjack

# Rules
I mostly used the basic rules from Wikipedia.  I did not implement betting or special "casino" rules since this is a simple program.

>Players are each dealt two cards, face up or down depending on the casino and the table at which you sit. In the U.S., the dealer is also dealt two cards, normally one up (exposed) and one down (hidden). In most other countries, the dealer receives one card face up. The value of cards two through ten is their pip value (2 through 10). Face cards (Jack, Queen, and King) are all worth ten. Aces can be worth one or eleven. A hand's value is the sum of the card values. Players are allowed to draw additional cards to improve their hands. A hand with an ace valued as 11 is called "soft", meaning that the hand will not bust by taking an additional card; the value of the ace will become one to prevent the hand from exceeding 21. Otherwise, the hand is "hard".

>Once all the players have completed their hands, it is the dealer’s turn. The dealer hand will not be completed if all players have either busted or received blackjacks. The dealer then reveals the hidden card and must hit until the cards total 17 or more points. (At most tables the dealer also hits on a "soft" 17, i.e. a hand containing an ace and one or more other cards totaling six.) Players win by not busting and having a total higher than the dealer, or not busting and having the dealer bust, or getting a blackjack without the dealer getting a blackjack. If the player and dealer have the same total (not counting blackjacks), this is called a "push", and the player typically does not win or lose money on that hand. Otherwise, the dealer wins. 

# Building
I used vscode.  I create a tasks.json for the compile.  Below is the general command.  This code should work with any gcc-ish compiler.

```
g++ -g main.cpp src/card.cpp src/deck.cpp src/player.cpp src/dealer.cpp -Iinclude
```

I also do have expierence with autotools/make and meson if you would like create the build that way as well.

## C++ Version
I am using the default option for the compiler which I belive is -std=c++17.

## Compiler
I used MinGW for windows.

```
C:\Users\Nicholas\Documents\Blackjack>g++ --version
g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

# Shuffle

I tried to use [std::shuffle](https://en.cppreference.com/w/cpp/numeric/random/random_device), but that did not work out due to a minmgw bug (see below).

> Notes
> A notable implementation where std::random_device is deterministic is MinGW ([bug 338](https://sourceforge.net/p/mingw-w64/bugs/338/)), although replacement implementations exist, such as [mingw-std-random_device](https://github.com/euloanty/mingw-std-random_device). 

I tried a few other methods, including [mingw-std-random_device](https://github.com/euloanty/mingw-std-random_device), but my CPU does not support RSEED.  I ended up using a spesfic time seed instead.  It is proably not as portable or good, but it gets the job done for this project.

# Documentation
Currently I did not make any documentation beyond basic comments in the code.  If you would like to see documentation let me know and I can submit some.

# Output
The formating for the output could use some work.  