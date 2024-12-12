#ifndef ADVISOR_H
#define ADVISOR_H

#include <string>
using namespace std;

struct Advisor
{
    int id;
    string name;
    string description;
};

#endif

/*
1. Rafiki - Invisibility (the ability to become un-seen)
2. Nala - Night Vision (the ability to see clearly in darkness)
3. Sarabi - Energy Manipulation (the ability to shape and control the properties of energy)
4. Zazu - Weather Control (the ability to influence and manipulate weather patterns)
5. Sarafina - Super Speed (the ability to run 4x faster than the maximum speed of lions)

Description | PathType (0 = cubTraining; 1 = straight to the pride lands; 2 = either path) | Advisor (0 = none; 1 = Rafiki; 2 = Nala; 3 = Sarabi; 4 = Zazu; 5 = Sarafina) | PridePoints (lose or gain)
Desert storm sweeps through the territory|2|4|-500
Fatigue from intense training with pride warriors|0|3|-200
Challenging night watch duty under pitch-black conditions|1|2|-400
Extra energy from bountiful season|1|0|800
Observed a rare natural phenomenon|0|0|600
Gained wisdom from observing Rafiki’s rituals|1|0|500
*/