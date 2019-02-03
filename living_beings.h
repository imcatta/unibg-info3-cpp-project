#ifndef _LIVING_BEINGS_
#define _LIVING_BEINGS_

#include <iostream>

using namespace std;

class LivingBeing
{
private: // optional, "private" by default
  string name;
  int age;
  friend ostream &operator<<(ostream &os, const LivingBeing &living_being);

public:
  LivingBeing(const string &, const int);
  bool operator<(const LivingBeing &other) const;
  int get_age() const;
  virtual int get_human_age() const;
};

// using virtual inheritance to solve the diamond inheritance problem
class WaterAnimal : virtual public LivingBeing
{
public:
  WaterAnimal(const string &, const int);
};

class Mammal : virtual public LivingBeing
{
public:
  Mammal(const string &, const int);
};

// diamond inheritance
// https://isocpp.org/wiki/faq/multiple-inheritance#mi-diamond
class Dolphin : public WaterAnimal, public Mammal
{
public:
  Dolphin(const string &, const int);
  int get_human_age() const override;
  // The `override` keyword behaves like the `@Override()` annotation in java.
  // In a member function declaration or definition, override ensures that
  // the function is virtual and is overriding a virtual function from a base class.
  // The program is ill-formed (a compile-time error is generated) if this is not true.
};

class Dog : public Mammal
{
public:
  Dog(const string &, const int);
  int get_human_age() const override;
};

#endif
