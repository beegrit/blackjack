//
// Created by becke on 6/10/2023.
//

#include "simulate.h"
#include <iostream>
#include <cstdlib>
#include <initializer_list>


void simulate::makeDeck(int size) {
    char cards[13] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};

    for (char card : cards) {
        for (int p = 0; p < 4 * size; p++) {
            deck.push_back(card);
        }
    }
}

char simulate::getCard() {
    srand((unsigned) time(NULL));
    int randCardIndex = rand()%deck.size();
    char randCard = deck[randCardIndex];
    deck.erase(deck.begin()+randCardIndex);
    return randCard;
}

std::vector<char> simulate::makeHand() {
    return std::vector<char> {getCard(),getCard()};
}
int simulate::cardToInt(char card) {
    if (card == 'A') {
        return 11;
    } else if (card == 'K' || card == 'Q' || card == 'J' || card == 'T') {
        return 10;
    } else {
        return card - '0';
    }
}
std::vector<int> simulate::handSum(std::vector<char> hand) {
    std::vector<int> cardVals;
    int sum = 0;
    int ace = 0;
    int dbl = 0;

    for (char card : hand) {
        int cardVal = cardToInt(card);
        if (cardVal == 11) {ace+=1;}
        cardVals.push_back(cardVal);
    }
    for (int i : cardVals) {sum+=i;}
    if (hand.size() == 2 && sum/2 == cardVals[0]) {
        dbl = 1;
    }
    if (sum > 21 && ace > 0) {
        sum -= 10;
        ace -= 1;
    }
    return std::vector<int> {sum,ace,dbl};
}
simulate::simulate() {
    makeDeck(1);
    bjRatio = 1.5;
    playerHand = makeHand();
    dealerHand = makeHand();
}
simulate::simulate(int decks) {
    makeDeck(decks);
    playerHand = makeHand();
    dealerHand = makeHand();
}


char simulate::bestChoice(std::vector<char> hand, char cDealerCard) {
    int dealerCard = cardToInt(cDealerCard);
    std::vector<int> sums = handSum(hand);
    if (sums[0] >= 18 and sums[1] == 0) {
        return 'S';
    } else if (sums[0] == 17 and sums[1] == 0) {
        return 'S';
    } else if (sums[0]<=16 and sums[0]>=13 and sums[1] == 0 and sums[2] == 0) {
        if (dealerCard > 6) {
            return 'H';
        } else {
            return 'S';
        }
    } else if (sums[0] == 12 and sums[1] == 0 and sums[2] == 0) {
        if (dealerCard<4 or dealerCard>6) {
            return 'H';
        } else {
            return 'S';
        }
    } else if (sums[0] == 11 and sums[1] == 0 and sums[2] == 0) {
        return 'D';
    } else if (sums[0] == 10 and sums[1] == 0 and sums[2] == 0) {
        if (dealerCard<10) {
            return 'D';
        } else {
            return 'H';
        }
    } else if (sums[0] == 9 and sums[1] == 0 and sums[2] == 0) {
        if (dealerCard == 2 or dealerCard > 6) {
            return 'H';
        } else {
            return 'D';
        }
    } else if (sums[0] == 8 and sums[1] == 0 and sums[2] == 0) {
        return 'H';
    } else if (sums[0] == 20 and sums[1] == 1) {
        return 'S';
    } else if (sums[0] == 19 and sums[1] == 1) {
        if (dealerCard != 6) {
            return 'S';
        } else {return 'D';}
    } else if (sums[0] = 18 and sums[1] == 1) {
        if (dealerCard <= 6) {
            return 'D';
        } else if (dealerCard >= 9) {
            return 'H';
        } else {return 'S';}
    } else if (sums[0] == 17 and sums[1] == 1) {
        if (dealerCard == 2 or dealerCard >= 7) {
            return 'H';
        } else {return 'D';}
    } else if (sums[0] == 16 or sums[0] == 15 and sums[1] == 1) {
        if (dealerCard >= 4 and dealerCard <=6) {
            return 'D';
        } else {return 'H';}
    } else if (sums[0] < 15 and sums[1] == 1) {
        if (dealerCard == 5 or dealerCard == 6) {
            return 'D';
        } else {return 'H';}
    } else if (sums[1] == 1 and sums[2] == 1) {
        return 'T';
    } else if (sums[0] == 20 and sums[2] == 1) {
        return 'S';
    } else if (sums[0] == 18 and sums[2] == 1) {
        if (dealerCard == 7 or dealerCard >= 10) {
            return 'S';
        } else {return 'T';}
    } else if (sums[0] == 16 and sums[2] == 1) {
        return 'T';
    } else if (sums[0] == 14 and sums[2] == 1) {
        if (dealerCard <= 7) {
            return 'T';
        } else {return 'H';}
    } else if (sums[0] == 12 and sums[2] == 1) {
        if (dealerCard<=6) {
            return 'T';
        } else {return 'H';}
    } else if (sums[0] == 10 and sums[2] == 1) {
        if (dealerCard<=9) {
            return 'D';
        } else {return 'H';}
    } else if (sums[0] == 8 and sums[2] == 1) {
        return 'H';
    } else if (sums[0] <= 6 and sums[2] == 1) {
        if (dealerCard <= 7) {
            return 'T';
        } else {return 'H';}
    } else if (sums[0] < 8) {
        return 'H';
    }
}

int simulate::playHand(int bet) {
    std::vector<std::vector<char>> playerHands {{playerHand}};
    std::vector<int> handValues;
    if (handSum(playerHand)[0] == 21) {
        if (handSum(dealerHand)[0] == 21) {
            return 0;
        } else {
            return bet*bjRatio;
        }
    }

    while (playerHands.size() > 0) {
        bestChoice(playerHands[0],dealerHand[0]);
    }

    return 0;
}




