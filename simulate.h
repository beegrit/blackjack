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
    double bjRatio;
    int cash;

    simulate(double bjRat, int decks);

    void init(int decks, float bjRatio);
    void makeDeck(int size);
    char getCard();
    std::vector<char> makeHand();
    int cardToInt(char card);
    std::vector<int> handSum(std::vector<char> hand);
    char bestChoice(std::vector<int> sums,char cDealerCard);
    int playHand(int bet);
    void runIt(int hands, int startCash, int bet);
private:



};


#endif //BLACKJACK_SIMULATE_H
