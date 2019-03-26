#include "lab4.h"

ListNode::ListNode(int val, ListNode *prev, ListNode *next) :
        prev(prev),
        next(next),
        val(val) {}

LinkedList::LinkedList() :
        first(nullptr),
        last(nullptr),
        size(0) {}

LinkedList::LinkedList(LinkedList const &right) :
        first(nullptr),
        last(nullptr),
        size(0) {
    if (right.first == nullptr) {
        first = nullptr;
        last = nullptr;
    } else {
        ListNode *node = right.first;
        while (node != nullptr) {
            push_back(node->val);
            node = node->next;
        }
    }
}

LinkedList &LinkedList::operator=(LinkedList const &right) {
    while (size > 0)
        pop_back();

    if (right.first != nullptr) {
        ListNode *node = right.first;
        while (node != nullptr) {
            push_back(node->val);
            node = node->next;
        }
    }

    return *this;
}

bool LinkedList::operator==(LinkedList const &right) const {
    return this->size == right.size;
}

bool LinkedList::operator!=(LinkedList const &right) const {
    return this->size != right.size;
}

bool LinkedList::operator>(LinkedList const &right) const {
    return this->size > right.size;
}

bool LinkedList::operator<(LinkedList const &right) const {
    return this->size < right.size;
}

bool LinkedList::operator<=(LinkedList const &right) const {
    return this->size <= right.size;
}

bool LinkedList::operator>=(LinkedList const &right) const {
    return this->size >= right.size;
}

int LinkedList::push_back(int const &val) {
    if (last == nullptr) {
        first = new ListNode(val);
        last = first;
    } else {
        ListNode *node = last;
        node->next = new ListNode(val, node);
        last = node->next;
    }
    size++;
    return 0;
}

int LinkedList::push_front(int const &val) {
    if (first == nullptr) {
        first = new ListNode(val);
        last = first;
    } else {
        ListNode *node = first;
        node->prev = new ListNode(val, nullptr, node);
        first = node->prev;
    }
    size++;
    return 0;
}

int LinkedList::pop_back() {
    if (last != nullptr) {
        ListNode *node = last;
        last = node->prev;
        if (last != nullptr)
            last->next = nullptr;
        else first = nullptr;
        int tmp = node->val;

        size--;
        delete node;
        return tmp;
    } else return 0;
}

int LinkedList::pop_front() {
    if (first != nullptr) {
        ListNode *node = first;
        first = node->next;
        if (first != nullptr)
            first->prev = nullptr;
        else last = nullptr;
        int tmp = node->val;

        size--;
        delete node;
        return tmp;
    } else return 0;
}

int LinkedList::getpos(int const &val) const {
    ListNode *node = first;
    int pos = 0;
    while (node != nullptr) {
        if (node->val == val)
            break;
        node = node->next;
        pos++;
    }
    if (node == nullptr)
        return 0;
    else return pos;
}

void LinkedList::print() {
    std::cout << "Int Linked List: " << std::endl;
    for (ListNode *node = first; node != nullptr; node = node->next) {
        std::cout << node->val << " ";
    }
    std::cout << std::endl;
}

void SortLinkedList::quicksort() {
    partition(getfirst(), getlast());
}

void SortLinkedList::partition(ListNode *start, ListNode *sup) {
    ListNode *after_sup = sup->next;
    sup->next = nullptr;
    ListNode *before_start = start->prev;
    start->prev = nullptr;

    ListNode *end = sup;
    ListNode *tmp = nullptr;
    ListNode *node = start;
    while (node != sup) {
        tmp = node->next;
        if (node->val >= sup->val) {
            if (node == start)
                start = start->next;

            if (node->prev != nullptr)
                node->prev->next = node->next;
            if (node->next != nullptr)
                node->next->prev = node->prev;

            end->next = node;
            node->prev = end;
            node->next = nullptr;
            end = node;
        }

        node = tmp;
    }

    start->prev = before_start;
    if (before_start != nullptr)
        before_start->next = start;
    end->next = after_sup;
    if (after_sup != nullptr)
        after_sup->prev = end;

    if (start->prev == nullptr)
        getfirst() = start;
    if (end->next == nullptr)
        getlast() = end;

    if (start != sup)
        partition(start, sup->prev);
    if (sup != end)
        partition(sup->next, end);
}

int LinkedList::getsize() {
    return size;
}

ListNode *&LinkedList::getlast() {
    return last;
}

ListNode *&LinkedList::getfirst() {
    return first;
}

ListNode *LinkedList::getlower(int const & val) {
    ListNode *node = first;
    if (node == nullptr || node->val > val)
        return nullptr;

    while (node->next != nullptr && node->next->val < val)
        node = node->next;
    return node;
}

int & LinkedList::refsize() {
    return size;
}

int SortLinkedList::push(int const &val) {
    ListNode *node = getlower(val);
    if (node != nullptr) {
        node->next = new ListNode(val, node, node->next);
        if (node->next->next != nullptr)
            node->next->prev = node->next;
        if (node == getlast())
            getlast() = node->next;
        refsize()++;
    } else LinkedList::push_front(val);

    return 0;
}
