#include <iostream>
#include "simulate.h"

int main() {
    simulate sim;
    //std::vector<int> playHand = sim.handSum({'Q','K'});
    //std::cout << sim.handSum({'A','J'})[0] << std::endl;
    std::cout << sim.playerHand[0] << " " << sim.playerHand[1] << std::endl;

    std::cout << sim.dealerHand[0] << std::endl;
    std::cout << sim.bestChoice(sim.handSum(sim.playerHand), sim.dealerHand[0]) << std::endl;

    return 0;
}
