#include <iostream>
#include <cmath>
#include <ctime>
#include <iterator>
#include <vector>
#include <fstream>
#include <algorithm>
#include "lab10.h"

int main() {
#define AVLSET_TEST

#ifdef LAB10
    AVLSet<int> avl;

    avl.AddKey(10);
    avl.AddKey(2);
    avl.AddKey(17);
    avl.AddKey(23);

    for (auto it = avl.begin(); it != avl.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::vector<int> vect = {0, 2, 7, 3, 10, 15};

    avl.Assign(vect.begin(), vect.end());

    for (auto it = avl.begin(); it != avl.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    auto it = avl.Find(7);
    std::cout << *it << std::endl;


    std::vector<int> vect = {1, 29, 17, 5, 3, 100, 72, 34, 23, 40};
    AVLSet<int> avl;
//    avl.Assign(vect.begin(), vect.end());

    avl.Insert(1);
    avl.Insert(29);
    avl.Insert(17);
    avl.Insert(5);
    avl.Insert(3);
    avl.Insert(100);
    avl.Insert(72);
    avl.Insert(34);
    avl.Insert(23);
    avl.Insert(40);

    for (auto it = avl.begin(); it != avl.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    return 0;
#endif

#ifdef AVLSET_TEST

    using namespace std;
    ifstream in("avlset.in");
    ofstream out("avlset.out");
    // read the number of actions we'll do
    int actions = 0;
    in >> actions;
    // make new tree object
    AVLSet<long long> avl;

    long long val = 0;
    char command = 0;
    AVLSetItem<long long> *item = nullptr;
    for (int i = 0; i < actions; i++) {
        in >> command;
        in >> val;

        if (command == 'A') {
            avl.Insert(val);
            // A is for add
            out << avl.Root()->balance_ << endl;
        }

        else if (command == 'D') { // d is for delete
            avl.Remove(val);
            if (avl.Root() == nullptr)
                out << 0 << endl;
            else out << avl.Root()->balance_ << endl;
        }

        else if (command == 'C') { // c is for check
           auto it = avl.Find(val);
            if (it == avl.end() || val != *it)
                out << 'N' << endl;
            else out << 'Y' << endl;

        }

    }
    // close files and delete tree finally
    in.close();
    out.close();

    return 0;
#endif


}