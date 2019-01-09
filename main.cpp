#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

#include "living_beings.h"
#include "humans.h"

using namespace std;

template <class T>
void print_vector(vector<T> &vec)
{
    for (auto e : vec) // C++11 feature
    {
        cout << e << endl;
    }
    // or alternatively
    // for (auto iter = vec.begin(); iter != vec.end(); ++iter)
    // {
    //     cout << *iter << endl;
    // }
}

template <class V>
void print_vector_of_ptr(vector<V *> &vec)
{
    for (auto e : vec)
    {
        cout << *e << endl;
    }
}

int main()
{
    Human h1("Alice", 24, "11111");
    Human h2("Bob", 19, "22222");
    Human h3("Carol", 52, "33333");
    Human h4("Dave", 26, "44444");

    try
    {
        Human h5("Eve", 33, "5555a");
    }
    catch (InvalidPhoneNumberException &e)
    // exception handling is an example of dynamic scope
    // usage in modern languages
    // https://users.dcc.uchile.cl/~etanter/scope/When_is_Dynamic_Scope_Useful_.html
    {
        cerr << e.what() << endl;
    }

    h1.add_friend(h2);
    h1.add_friend(h3);
    h1.add_friend(h4);
    assert(h1.friends_count() == 3);

    // try to add an already added friend
    h1.add_friend(h2);
    // nothing happens
    assert(h1.friends_count() == 3);

    cout << "Calling friends" << endl;
    h1.call_friends();

    h1.remove_friend(h4);
    assert(h1.friends_count() == 2);

    LivingBeing living_being("Ralph", 122);
    WaterAnimal water_animal("Nemo", 8);
    Mammal mammal("Manny", 34);
    Dolphin dolphin("Flipper", 3);
    Dog dog("Fido", 5);

    vector<LivingBeing> vec;
    vec.push_back(h1);
    vec.push_back(h2);
    vec.push_back(h3);
    vec.push_back(h4);
    vec.push_back(living_being);
    vec.push_back(water_animal);
    vec.push_back(mammal);
    vec.push_back(dolphin);
    vec.push_back(dog);

    cout << "---------------" << endl;
    cout << "Pre sorting" << endl;
    print_vector(vec);
    cout << "---------------" << endl;

    // vec will be sorted using the `<` operator
    sort(vec.begin(), vec.end());

    cout << "After sorting" << endl;
    print_vector(vec);
    cout << "---------------" << endl;

    // lambda - C++11 feature
    auto comp = [](LivingBeing &l1, LivingBeing &l2) { return l1.get_human_age() < l2.get_human_age(); };
    sort(vec.begin(), vec.end(), comp);
    cout << "After custom sorting" << endl;
    print_vector(vec);

    // As you can see sorting by `get_human_age()` does not work.
    // It's because the type of `vec` is `vector<LivingThing>`,
    // so objects are "sliced" when inserted into the vector.
    cout << endl
         << endl
         << endl;

    // To solve the issue we should use a vector of pointers to LivingBeing
    vector<LivingBeing *> vec_of_ptr;
    vec_of_ptr.push_back(&h1);
    vec_of_ptr.push_back(&h2);
    vec_of_ptr.push_back(&h3);
    vec_of_ptr.push_back(&h4);
    vec_of_ptr.push_back(&living_being);
    vec_of_ptr.push_back(&water_animal);
    vec_of_ptr.push_back(&mammal);
    vec_of_ptr.push_back(&dolphin);
    vec_of_ptr.push_back(&dog);

    auto comp_ptr = [](LivingBeing *l1, LivingBeing *l2) { return l1->get_human_age() < l2->get_human_age(); };
    sort(vec_of_ptr.begin(), vec_of_ptr.end(), comp_ptr);
    cout << "---------------" << endl;
    cout << "PTR - After sorting by human age" << endl;
    print_vector_of_ptr(vec_of_ptr);
    // now it works as expected

    // A disadvantage of this tecnique is that because we are dealing with LivingBeing pointers,
    // we can no longer natively take advantage of the `<` operator overload.
    // But it's easy to fix that
    auto comp_ptr_by_age = [](LivingBeing *l1, LivingBeing *l2) { return *l1 < *l2; };
    cout << "---------------" << endl;
    cout << "PTR - After sorting by age" << endl;
    sort(vec_of_ptr.begin(), vec_of_ptr.end(), comp_ptr_by_age);
    print_vector_of_ptr(vec_of_ptr);
    // Moreover, by using LivingBeing pointers the objects are not cloned inside
    // the vector, so we have less memory usage

    //
    // return EXIT_SUCCESS;
    //
    // In C++, main() need not contain an explicit return statement.
    // In that case, the value returned is 0, meaning successful execution.
    // http://www.stroustrup.com/bs_faq2.html#void-main
}
