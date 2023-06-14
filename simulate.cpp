//
// Created by becke on 6/10/2023.
//

#include "simulate.h"
#include <iostream>
#include <cstdlib>


void simulate::makeDeck(int size) {
    char cards[13] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
    deck = {};
    for (char card : cards) {
        for (int p = 0; p < 4 * size; p++) {
            deck.push_back(card);
        }
    }
}

char simulate::getCard() {
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
simulate::simulate(double bjRat, int decks) {
    bjRatio = bjRat;
    deckCount = decks;
}

void simulate::init(int decks, float bjRatio) {
    makeDeck(decks);
    bjRatio = bjRatio;
    playerHand = makeHand();
    dealerHand = makeHand();
}

char simulate::bestChoice(std::vector<int> sums, char cDealerCard) {
    int dealerCard = cardToInt(cDealerCard);
    if (sums[0] >= 18 and sums[1] == 0) {
        return 'S';
    } else if (sums[0] == 17 and sums[1] == 0) {
        return 'S';
    } else if ((sums[0]<=16 and sums[0]>=13) and sums[1] == 0 and sums[2] == 0) {
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
    return 'S';
}

int simulate::playHand(int bet) {
    std::vector<std::vector<char>> playerHands {{playerHand}};
    std::vector<std::vector<int>> handValues;
    int betSum = 0;
    if (handSum(playerHand)[0] == 21) {
        if (handSum(dealerHand)[0] == 21) {
            return 0;
        } else {
            return bet*bjRatio;
        }
    }

    while (playerHands.size() > 0) {
        std::vector<int> playerSum = handSum(playerHands[0]);
        char choice = bestChoice(playerSum,dealerHand[0]);
        if (choice == 'H') {
            playerHands[0].push_back(getCard());
        } else if (choice == 'S') {
            handValues.push_back({playerSum[0],bet});
            playerHands.erase(playerHands.begin()+0);
        } else if (choice == 'D') {
            playerHands[0].push_back(getCard());
            playerSum = handSum(playerHands[0]);
            handValues.push_back({playerSum[0],bet*2});
            playerHands.erase(playerHands.begin()+0);
        } else if (choice == 'T') {
            playerHands.push_back({playerHands[0][1]});
            playerHands[0].erase(playerHands[0].begin()+1);
        }

    }

    for (int i = 0; i<handValues.size(); i++ ) {
        if (handValues[i][0] > 21) {
            betSum -= handValues[i][1];
            handValues.erase(handValues.begin()+i);
        }
    }
    std::vector<int> dealerSum = handSum(dealerHand);
    while (dealerSum[0] < 17 or (dealerSum[0] == 17 and dealerSum[1] > 1)) {
        dealerHand.push_back(getCard());
        dealerSum = handSum(dealerHand);
    }
    if (dealerSum[0] > 21) {
        for (int i = 0; i < handValues.size(); i++) {
            betSum += handValues[i][1];
            return betSum;
        }
    }
    for (int i = 0; i<handValues.size(); i++ ) {
        if (handValues[i][0] > dealerSum[0]) {
            betSum += handValues[i][1];
        } else if (handValues[i][0] < dealerSum[0]) {
            betSum -= handValues[i][1];
        }
    }

    std::cout << "ran" << std::endl;
    return betSum;
}

void simulate::runIt(int hands, int startCash, int bet) {
    srand(time(NULL));
    cash = startCash;
    for (int i = 0; i < hands; i++) {
        init(deckCount, bjRatio);
        cash += playHand(bet);
        std::cout << deck.size() << std::endl;
    }
    std::cout << "Player has $" << cash << " left" << std::endl;

}






