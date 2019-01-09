#include <string>
#include <algorithm>
#include <set>

#include "humans.h"
#include "living_beings.h"

bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

const char *InvalidPhoneNumberException::what() const throw()
{
    return "Phone numbers must contain digits only";
}

SmartPhone::SmartPhone(const std::string &phone_number) : phone_number(phone_number)
{
    if (!is_digits(phone_number))
    {
        throw InvalidPhoneNumberException();
    }
};

bool SmartPhone::operator==(const SmartPhone &other) const
{
    return this->phone_number == other.phone_number;
}

void SmartPhone::call(const string &other) const
{
    cout << phone_number << " is calling " << other << endl;
}

void SmartPhone::call(const SmartPhone &other) const
{
    call(other.phone_number);
};

Human::Human(const std::string &name, const int age, const std::string &phone_number) : LivingBeing(name, age),
                                                                                        Mammal(name, age),
                                                                                        SmartPhone(phone_number)
{
    // `friends` is allocated using "new"
    // must be explicitly deleted in the destructor
    friends = new set<Human>;
}

Human::~Human()
{
    delete friends;
}

void Human::add_friend(const Human &new_friend)
{
    friends->insert(new_friend);
}

void Human::remove_friend(const Human &old_friend)
{
    friends->erase(old_friend);
}

void Human::call_friends() const
{
    for (auto iter = friends->begin(); iter != friends->end(); ++iter)
    {
        call(iter->phone_number);
    }
};

int Human::friends_count() const
{
    return friends->size();
}