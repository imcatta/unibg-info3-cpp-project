#include <iostream>

#include "living_beings.h"

using namespace std;

ostream &operator<<(std::ostream &os, const LivingBeing &living_being)
{
    return os << living_being.name
              << " - Age: " << living_being.age
              << " - Human Age: " << living_being.get_human_age();
};

LivingBeing::LivingBeing(const string &name, const int age) : name(name),
                                                              age(age) {}
bool LivingBeing::operator<(const LivingBeing &other) const
{
    return this->age < other.age;
}
int LivingBeing::get_age() const
{
    return age;
}
int LivingBeing::get_human_age() const
{
    return age;
};

WaterAnimal::WaterAnimal(const string &name, const int age) : LivingBeing(name, age){};

Mammal::Mammal(const string &name, const int age) : LivingBeing(name, age){};

Dolphin::Dolphin(const string &name, const int age) : LivingBeing(name, age),
                                                      WaterAnimal(name, age),
                                                      Mammal(name, age){};
int Dolphin::get_human_age() const
{
    return get_age() * 4;
};

Dog::Dog(const string &name, const int age) : LivingBeing(name, age),
                                              Mammal(name, age){};
int Dog::get_human_age() const
{
    return get_age() * 7;
};
