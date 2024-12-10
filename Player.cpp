#include "Player.h"
#include <iostream>
#include <iomanip>
using namespace std;

/*
string _name;
int _strength, _stamina, _wisdom, _pride_points, _age;
*/

Player::Player()
{
    _name = "";
    _strength = 100;
    _stamina = 100;
    _wisdom = 100;
    _pride_points = 0;
    _age = 1;
}

Player::Player(string name, int age, int strength, int stamina, int wisdom, int pride_points)
{
    _name = name;
    _age = age;
    _strength = constrainIntToRange(strength, 100, 1000);
    _stamina = constrainIntToRange(stamina, 100, 1000);
    _wisdom = constrainIntToRange(wisdom, 100, 1000);
    _pride_points = pride_points;
}

string Player::getName()
{
    return _name;
}

int Player::getStrength()
{
    return _strength;
}

int Player::getStamina()
{
    return _stamina;
}

int Player::getWisdom()
{
    return _wisdom;
}

int Player::getPridePoints()
{
    return _pride_points;
}

int Player::getAge()
{
    return _age;
}

void Player::setName(string name)
{
    _name = name;
}

void Player::addStrength(int strength)
{
    _strength += strength;
}

void Player::addStamina(int stamina)
{
    _stamina += stamina;
}

void Player::addWisdom(int wisdom)
{
    _wisdom += wisdom;
}

void Player::addPridePoints(int pride_points)
{
    _pride_points += pride_points;
}

void Player::addAge(int years)
{
    _age += years;
}

void Player::trainCub(int strength, int stamina, int wisdom)
{
    _strength = constrainIntToRange(strength, 100, 1000);
    _stamina = constrainIntToRange(stamina, 100, 1000);
    _wisdom = constrainIntToRange(wisdom, 100, 1000);
    _pride_points -= 5000;
}

void Player::toPrideLands()
{
    _pride_points += 5000;
    _strength -= 2000;
    _wisdom -= 2000;
    _stamina -= 1000;
}

void Player::printStats()
{
    cout << "##############################\n"
         << "# " << _name << ", age " << _age << fixed << setw(22 - static_cast<int>(_name.length())) << " #\n"
         << "# Strength: " << fixed << setw(16) <<                                          _strength << " #\n"
         << "# Stamina: " << fixed << setw(17) <<                                            _stamina << " #\n"
         << "# Wisdom: " << fixed << setw(18) <<                                              _wisdom << " #\n"
         << "# Pride Points: " << fixed << setw(12) <<                                  _pride_points << " #\n"
         << "##############################\n";
}

// Little utility function to make life easier
int Player::constrainIntToRange(int input, int min, int max)
{
    if (input < min)
        return min;
    else if (input > max)
        return max;
    else
        return input;
}
