#include <iostream>
#include "simulate.h"
int main() {

    simulate sim = simulate(1.5,1);

    sim.runIt(1000, 100000, 500);


    return 0;
}
