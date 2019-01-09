// "#ifndef ... #define" is an include guard.
// It's used to avoid the same header file being included
// multiple times (via different routes) within the same CPP file,
// which would lead to multiple-definition errors.
#ifndef _HUMANS_
#define _HUMANS_

#include <string>
#include <set>

#include "living_beings.h"

// c++ exceptions are controversial
// for instance, google don't use them
// https://google.github.io/styleguide/cppguide.html#Exceptions
class InvalidPhoneNumberException : public std::exception
{
public:
  const char *what() const throw();
};

// structs and classes are the almost the same thing.
// the only difference is that struct's members are public by default,
// class's members are private by default
struct SmartPhone
{
protected:
  string phone_number;

public:
  SmartPhone(const string &);
  bool operator==(const SmartPhone &) const;
  void call(const string &) const;
  // overload
  void call(const SmartPhone &) const;
};

// public inheritance means that `Human` "is a" `Mammal`
// private inheritance means that `Human` "has a" `SmartPhone`s
class Human : public Mammal, private SmartPhone
{
private:
  set<Human> *friends;

public:
  Human(const string &, const int, const string &);
  ~Human();
  void add_friend(const Human &);
  void remove_friend(const Human &);
  void call_friends() const;
  int friends_count() const;
};

#endif