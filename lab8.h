#include <iostream>
#include <vector>
#include <forward_list>
#include <typeinfo>
#include <typeindex>
#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <array>
#include <memory>

template<class C>
class Condition {
public:
    bool operator()(C &container, typename C::iterator it) = 0;
};

template<>
class Condition<std::vector<int>> {
public:
    bool operator()(std::vector<int> &vect, std::vector<int>::iterator it) {
        return (it < (vect.end() - 1) ? (*it > *(it + 1)) : true);
    }
    bool operator()(std::vector<int>::iterator it) {
        return *it > 5;
    }
};

class int_compare {
public:
    bool operator() (int val) {
        return val > 10;
    }
};

class str_condition {
public:
    bool operator()(std::string const &str) {
        return str.length() > 5;
    }
};

class str_sorted {
public:
    bool operator() (std::string const &lhs, std::string const &rhs) {
        return lhs < rhs;
    }
};

struct exp {
    double degree;
};

class exp_equal {
public:
    bool operator()(exp const &lhs, exp const &rhs) {
        return lhs.degree == rhs.degree;
    }
};

template<template <typename> class Container, typename Cond>
bool none_of(Container<typename> &cont) {
    typename Container::iterator it = cont.begin();
    typename Container::iterator end = cont.end();
    Cond condition;

    bool none_of = true;
    while (it != end) {
        if (condition(*it)) {
            none_of = false;
            break;
        }

        ++it;
    }

    return none_of;
}

template<typename Cond>
bool none_of<Container<int>, Cond>(Container<int> &cont) {
    typename Container<int>::iterator it = cont.begin();
    typename Container<int>::iterator end = cont.end();
    Cond condition;

    bool none_of = true;
    while (it != end) {
        if (condition(*it)) {
            none_of = false;
            break;
        }

        ++it;
    }

    return none_of;
}

template<class Container, typename Cond>
bool any_of(Container &cont) {
    typename Container::iterator it = cont.begin();
    typename Container::iterator end = cont.end();
    Cond condition;

    bool any_of = false;
    while (it != end) {
        if (condition(*it)) {
            any_of = true;
            break;
        }

        ++it;
    }

    return any_of;
}

template<class Container, typename Cond>
bool all_of(Container &cont) {
    typename Container::iterator it = cont.begin();
    typename Container::iterator end = cont.end();
    Cond condition;

    bool all_of = true;
    while (it != end) {
        if (!condition(*it)) {
            all_of = false;
            break;
        }

        ++it;
    }

    return all_of;
}

template<class Container, typename Cond>
bool is_sorted(Container &cont) {
    Cond condition;
    typename Container::iterator it = cont.begin();
    typename Container::iterator end = cont.end() - 1;

    bool sorted = true;
    while (it != end) {
        if (!condition(*it, *(it + 1))) {
            sorted = false;
            break;
        }

        ++it;
    }

    return sorted;
}

template<class Container, typename Cond>
typename Container::iterator find_backward(Container &cont, typename Container::value_type const &val) {
    typename Container::iterator it = cont.end() - 1;
    typename Container::iterator begin = cont.begin();



    Cond condition;
    while (!condition(*it, val) && it != begin)
        --it;

    if (condition(*it, val))
        return it;
    else return cont.end();

}

int main() {

    std::vector<int> my_vect;
    std::vector<int> my_vect2;
    for (int i = 0; i < 10; ++i) {
        my_vect.push_back(i);
        my_vect2.push_back(i);
    }
    std::cout << (my_vect == my_vect2);


    std::unordered_map<std::type_index, std::string> type_names;

    type_names[std::type_index(typeid(int))] = "int";
    type_names[std::type_index(typeid(double))] = "double";
    type_names[std::type_index(typeid(std::string))] = "string";

    int i;
    std::vector<std::string>::value_type variable;
    std::cout << "i is " << type_names[std::type_index(typeid(i))] << '\n';
    typename std::iterator_traits<std::vector<int>::iterator>::value_type var = 10;
    std::cout << "i is " << type_names[std::type_index(typeid(var))] << '\n';
    std::cout << "i is " << type_names[std::type_index(typeid(variable))] << '\n';


    std::string buffer;
    while(true) {
//        std::forward_list<int> list;
//        std::vector<std::string> vect;
        std::vector<exp> vect;

        while (true) {
            std::cin >> buffer;
            if (buffer == "stop" || buffer == "exit")
                break;

            int val;
            val = std::stoi(buffer);
//            list.push_front(val);
//            list.push_front(buffer);
//            vect.push_back(buffer);
//            vect.push_back(val);
            vect.push_back({double(val)});

        }

        if (buffer == "exit")
            break;

        for (exp &val : vect)
            std::cout << val.degree << ' ';
        std::cout << std::endl;

//        std::cout << none_of<std::forward_list<int>, int_compare>(list) << std::endl;
        std::vector<exp>::iterator it = find_backward<std::vector<exp>, exp_equal>(vect, {4.0});
        std::cout << (*it).degree;

    }

    return 0;
}