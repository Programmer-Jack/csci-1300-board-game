#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
using namespace std;

class Player
{
private:
    string _name;
    int _strength, _stamina, _wisdom, _pride_points, _age;

    int constrainIntToRange(int, int, int);

public:
    Player();
    Player(string name, int strength, int stamina, int wisdom);

    string getName();
    int getStrength();
    int getStamina();
    int getWisdom();
    int getPridePoints();
    int getAge();

    void setName(string name);
    void addStrength(int strength);
    void addStamina(int stamina);
    void addWisdom(int wisdom);
    void addPridePoints(int pride_points);
    void addAge(int age);

    void trainCub(int strength, int stamina, int wisdom);
    void toPrideLands();
    void printStats();
};

#endif