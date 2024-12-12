#ifndef EVENT_H
#define EVENT_H

#include <string>
using namespace std;

struct Event
{
    string description;
    int path_type; // 0 = cubTraining; 1 = straight to the pride lands; 2 = either path
    int advisor_id; // 0 = none; 1 = Rafiki; 2 = Nala; 3 = Sarabi; 4 = Zazu; 5 = Sarafina
    int pride_point_delta;
};

#endif