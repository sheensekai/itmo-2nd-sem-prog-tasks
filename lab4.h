#ifndef PROGTASKSCPP_LAB4_H
#define PROGTASKSCPP_LAB4_H

#include <iostream>

struct ListNode {
    explicit ListNode(int val = 0, ListNode *prev = nullptr, ListNode *next = nullptr);

    ListNode *prev;
    ListNode *next;
    int val;
};

class LinkedList {
public:
    virtual int push_front(int const &val);

    virtual int push_back(int const &val);

    int pop_front();

    int pop_back();

    int getpos(int const &val) const;

    virtual int getsize();

    void print();

    LinkedList &operator=(LinkedList const &right);

    bool operator==(LinkedList const &right) const;

    bool operator!=(LinkedList const &right) const;

    bool operator>(LinkedList const &right) const;

    bool operator<(LinkedList const &right) const;

    bool operator<=(LinkedList const &right) const;

    bool operator>=(LinkedList const &right) const;

    LinkedList();

    LinkedList(LinkedList const &right);

    virtual ~LinkedList() = default;
protected:
    ListNode *&getfirst();
    ListNode *&getlast();
    ListNode *getlower(int const & val);
    int & refsize();

private:
    int size;
    ListNode *first;
    ListNode *last;
};

typedef LinkedList list;

class SortLinkedList : public LinkedList {
public:
    int push(int const & val);

    void quicksort();

    ~SortLinkedList() override = default;
private:
    int push_back(int const &val) override {
        return 0;
    }

    int push_front(int const &val) override {
        return 0;
    }

    void partition(ListNode *first, ListNode *last);
};

typedef SortLinkedList sortlist;
#endif //PROGTASKSCPP_LAB4_H
