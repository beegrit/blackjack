//
// Created by becke on 6/10/2023.
//

#ifndef BLACKJACK_SIMULATE_H
#define BLACKJACK_SIMULATE_H

#include <vector>
#include <list>

class simulate {
public:

    std::vector<char> playerHand;
    std::vector<char> dealerHand;
    std::vector<char> deck;
    int deckCount;
    float bjRatio;
    simulate();
    simulate(int decks);

    void makeDeck(int size);
    char getCard();
    std::vector<char> makeHand();
    int cardToInt(char card);
    std::vector<int> handSum(std::vector<char> hand);
    char bestChoice(std::vector<char>hand,char cDealerCard);
    int playHand(int bet);
private:



};


#endif //BLACKJACK_SIMULATE_H
