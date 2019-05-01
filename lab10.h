#ifndef PROGTASKSCPP_MY_AVL_SET_H
#define PROGTASKSCPP_MY_AVL_SET_H

#include <iterator>

#define AVLSET_DELETE 0
#define AVLSET_ADD 1

template<typename ValueType, class Compare> class AVLSetItem;
template<typename ValueType, class Compare> class AVLSet;
template<typename ValueType, class Compare> class AVLSetIterator;

template<typename ValueType, class Compare = std::less<ValueType>>
class AVLSet {

public:

    typedef ValueType value_type;
    typedef AVLSetIterator<ValueType, Compare> iterator;
    typedef AVLSetIterator<ValueType, Compare> const_iterator;
    typedef AVLSetItem<ValueType, Compare> Item;

    AVLSet();

    AVLSet(const AVLSet &other);

    AVLSet<ValueType, Compare> &operator=(const AVLSet &other);

    ~AVLSet();

    iterator Insert(const value_type &key);

    iterator Remove(const value_type &key);

    iterator Clear();

    iterator Find(const value_type &key);

    const_iterator Find(const value_type &key) const;

    iterator begin();

    const_iterator cbegin();

    iterator end();

    const_iterator cend();

    template <class InputIt>
    int Assign(InputIt first, InputIt last);

    const Item *Root();

    size_t Size();

private:
    Item *FindKey(value_type const &key);

    void Balance(Item *par, int mode);

    void HBRecalc(Item *par);

    Item *LLRotate(Item *par);

    Item *LBRotate(Item *par);

    Item *RLRotate(Item *par);

    Item *RBRotate(Item *par);

    Compare Comp;

    Item *root_;

    iterator begin_;

    const_iterator cbegin_;

    iterator end_;

    const_iterator cend_;

    size_t size_;
};

template<typename ValueType, class Compare = std::less<ValueType>>
class AVLSetItem {
public:

    friend class AVLSet<ValueType, Compare>;
    friend class AVLSetIterator<ValueType, Compare>;
    typedef AVLSetItem<ValueType, Compare> Item;
    typedef ValueType value_type;
    typedef AVLSetIterator<ValueType, Compare> iterator;
    typedef AVLSetIterator<ValueType, Compare> const_iterator;


    explicit AVLSetItem(ValueType key,
                        Item *parent = nullptr,
                        Item *left = nullptr,
                        Item *right = nullptr);

    ~AVLSetItem();

    Item *FindNextItem();

    Item *FindPrevItem();

    value_type key_;
    int balance_;
    int height_;

    Item *parent_;
    Item *left_;
    Item *right_;
};

template<typename ValueType, class Compare = std::less<ValueType>>
class AVLSetIterator : public std::iterator<std::bidirectional_iterator_tag, ValueType> {
public:
    friend class AVLSet<ValueType, Compare>;
    friend class AVLSetItem<ValueType, Compare>;

    typedef ValueType value_type;
    typedef AVLSetIterator<ValueType, Compare> iterator;
    typedef AVLSetIterator<ValueType, Compare> const_iterator;
    typedef AVLSetItem<ValueType , Compare> Item;

    explicit AVLSetIterator(Item *ptr);

    AVLSetIterator(iterator const &other);

    ~AVLSetIterator() = default;

    bool operator!=(iterator const &other) const;

    bool operator==(iterator const &other) const;

    ValueType operator*() const;

    ValueType const &operator*();

    AVLSetIterator &operator++();

    AVLSetIterator operator++(int);

    AVLSetIterator &operator--();

    AVLSetIterator operator--(int);

private:
    Item *item_ptr_;
};


template<typename ValueType, class Compare>
AVLSetIterator<ValueType, Compare>::AVLSetIterator(Item *ptr) :
        item_ptr_(ptr) {}

template<typename ValueType, class Compare>
AVLSetIterator<ValueType, Compare>::AVLSetIterator(iterator const &other) :
        item_ptr_(other.item_ptr_) {}

template<typename ValueType, class Compare>
bool AVLSetIterator<ValueType, Compare>::operator!=(iterator const &other) const {
    return item_ptr_ != other.item_ptr_;
}

template<typename ValueType, class Compare>
bool AVLSetIterator<ValueType, Compare>::operator==(iterator const &other) const {
    return item_ptr_ == other.item_ptr_;
}

template<typename ValueType, class Compare>
ValueType AVLSetIterator<ValueType, Compare>::operator*() const {
    return item_ptr_->key_;
}

template<typename ValueType, class Compare>
ValueType const &AVLSetIterator<ValueType, Compare>::operator*()  {
    return item_ptr_->key_;
}


template<typename ValueType, class Compare>
AVLSetIterator<ValueType, Compare> &AVLSetIterator<ValueType, Compare>::operator++() {
    item_ptr_ = item_ptr_->FindNextItem();
    return *this;
}

template<typename ValueType, class Compare>
AVLSetIterator<ValueType, Compare> AVLSetIterator<ValueType, Compare>::operator++(int) {
    AVLSetIterator<ValueType, Compare> tmp(*this);
    ++(*this);
    return tmp;
}

template<typename ValueType, class Compare>
AVLSetIterator<ValueType, Compare> &AVLSetIterator<ValueType, Compare>::operator--() {
    item_ptr_ = item_ptr_->FindPrevItem();
    return *this;
}

template<typename ValueType, class Compare>
AVLSetIterator<ValueType, Compare> AVLSetIterator<ValueType, Compare>::operator--(int) {
    AVLSetIterator<ValueType, Compare> tmp(*this);
    ++(*this);
    return tmp;
}

template<typename ValueType, class Compare>
AVLSetItem<ValueType, Compare>::AVLSetItem(value_type key, Item *par, Item *left, Item *right) :
        key_(key),
        balance_(0),
        height_(1),
        parent_(par),
        left_(left),
        right_(right) {}

template<typename ValueType, class Compare>
AVLSetItem<ValueType, Compare>::~AVLSetItem() {
    if (left_)
        delete left_;
    if (right_)
        delete right_;
}

template<typename ValueType, class Compare>
typename AVLSetItem<ValueType, Compare>::Item *AVLSetItem<ValueType, Compare>::FindNextItem() {
    Item *item_ptr = this;

    if (item_ptr->right_ != nullptr) {

        item_ptr = item_ptr->right_;
        while (item_ptr->left_ != nullptr)
            item_ptr = item_ptr->left_;

        return item_ptr;
    }

    else while (item_ptr->parent_ != nullptr) {
            if (item_ptr == item_ptr->parent_->left_)
                return item_ptr->parent_;

            item_ptr = item_ptr->parent_;
        }

    return nullptr;
}

template<typename ValueType, class Compare>
typename AVLSetItem<ValueType, Compare>::Item *AVLSetItem<ValueType, Compare>::FindPrevItem() {
    Item *item_ptr = this;

    if (item_ptr->left_ != nullptr) {

        item_ptr = item_ptr->left_;
        while (item_ptr->right_ != nullptr)
            item_ptr = item_ptr->right_;

        return item_ptr;
    }

    else while (item_ptr->parent_ != nullptr) {
            if (item_ptr == item_ptr->parent_->right_)
                return item_ptr->parent_;

            item_ptr = item_ptr->parent_;
        }

    return nullptr;
}

template<typename ValueType, class Compare>
AVLSet<ValueType, Compare>::AVLSet() :
        root_(nullptr),
        size_(0),
        begin_(iterator(nullptr)),
        cbegin_(const_iterator(nullptr)),
        end_(iterator(nullptr)),
        cend_(const_iterator(nullptr)) {}

template<typename ValueType, class Compare>
AVLSet<ValueType, Compare>::AVLSet(const AVLSet &other) : AVLSet() {
    for (iterator it = other.begin(); it != other.end(); ++it)
        Insert(*it);
}

template<typename ValueType, class Compare>
AVLSet<ValueType, Compare> &AVLSet<ValueType, Compare>::operator=(const AVLSet &other) {
    Clear();
    for (iterator it = other.begin(); it != other.end(); ++it)
        Insert(*it);
    return *this;
}

template<typename ValueType, class Compare>
AVLSet<ValueType, Compare>::~AVLSet() {
    delete root_;
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::iterator AVLSet<ValueType, Compare>::Insert(const value_type &key) {
    Item *par = FindKey(key);

    if (par == nullptr) {
        ++size_;
        root_ = new Item(key);

        begin_.item_ptr_ = root_;
        cbegin_.item_ptr_ = root_;

        return iterator(root_);
    }

    else if (key != par->key_) {
        ++size_;
        Item *node = new Item(key);

        if (Comp(key, par->key_))
            par->left_ = node;
        else par->right_ = node;
        node->parent_ = par;

        if (key < *begin_) {
            begin_.item_ptr_ = node;
            cbegin_.item_ptr_ = node;
        }

        Balance(par, AVLSET_ADD);
        return iterator(node);
    }

    else return iterator(nullptr);
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::iterator AVLSet<ValueType, Compare>::Remove(const value_type &key) {
    Item *node = FindKey(key);
    if (node == nullptr || key != node->key_)
        return iterator(end_);

    Item *par = node->parent_;
    if (node->left_ == nullptr && node->right_ == nullptr) {
        if (par == nullptr) {
            delete node;
            root_ = nullptr;
            --size_;
            return iterator(end_);
        } else {
            Item *next = node->FindNextItem();
            if (Comp(node->key_, par->key_))
                par->left_ = nullptr;
            else par->right_ = nullptr;
            delete node;
            --size_;
            Balance(par, AVLSET_DELETE);
            return iterator(next);
        }

    } else if (node->left_ != nullptr && node->right_ != nullptr) {
        Item *next = node->FindNextItem();
        Item *r_node = node->left_;
        while (r_node->right_ != nullptr)
            r_node = r_node->right_;

        ValueType tmp = r_node->key_;
        Item *check = nullptr;
        if (r_node->left_ != nullptr) {
            r_node->key_ = r_node->left_->key_;
            delete r_node->left_;
            r_node->left_ = nullptr;
            check = r_node;
        } else {
            Item *r_par = r_node->parent_;
            if (Comp(r_node->key_, r_par->key_))
                r_par->left_ = nullptr;
            else r_par->right_ = nullptr;
            delete r_node;
            check = r_par;
        }

        --size_;
        node->key_ = tmp;
        Balance(check, AVLSET_DELETE);
        return iterator(next);
    } else {
        Item *next = node->FindNextItem();
        if (node->left_ != nullptr) {
            node->key_ = node->left_->key_;
            delete node->left_;
            node->left_ = nullptr;
        } else {
            node->key_ = node->right_->key_;
            delete node->right_;
            node->right_ = nullptr;
        }

        --size_;
        Balance(node, AVLSET_DELETE);
        return iterator(next);
    }
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::iterator AVLSet<ValueType, Compare>::Clear() {
    delete root_;
    root_ = nullptr;
    return iterator(end_);
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::iterator AVLSet<ValueType, Compare>::Find(const value_type &key) {
    return iterator(FindKey(key));
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::const_iterator AVLSet<ValueType, Compare>::Find(const value_type &key) const {
    return const_iterator(FindKey(key));
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::iterator AVLSet<ValueType, Compare>::begin() {
    return begin_;
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::const_iterator AVLSet<ValueType, Compare>::cbegin() {
    return cbegin_;
}

template<typename ValueType, class Compare>
typename  AVLSet<ValueType, Compare>::iterator AVLSet<ValueType, Compare>::end() {
    return end_;
}

template<typename ValueType, class Compare>
typename  AVLSet<ValueType, Compare>::const_iterator AVLSet<ValueType, Compare>::cend() {
    return cend_;
}

template<typename ValueType, class Compare>
template<class InputIt>
int AVLSet<ValueType, Compare>::Assign(InputIt first, InputIt last) {
    Clear();
    while (first != last) {
        Insert(*first);
        ++first;
    }

    return 1;
}

template<typename ValueType, class Compare>
const typename AVLSet<ValueType, Compare>::Item *AVLSet<ValueType, Compare>::Root() {
    return root_;
}

template<typename ValueType, class Compare>
size_t AVLSet<ValueType, Compare>::Size() {
    return size_;
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::Item *AVLSet<ValueType, Compare>::FindKey(const value_type &key) {
    Item *node = root_;
    while (node != nullptr) {
        if (Comp(key, node->key_) && node->left_ != nullptr)
            node = node->left_;
        else if (Comp(node->key_, key) && node->right_ != nullptr)
            node = node->right_;
        else break;
    }

    return node;
}

template<typename ValueType, class Compare>
void AVLSet<ValueType, Compare>::Balance(Item *par, int mode) {
    while (true) {
        if (par == nullptr)
            return;

        HBRecalc(par);
        if (mode == AVLSET_ADD && par->balance_ == 0)
            return;

        if (mode == AVLSET_DELETE)
            if (par->balance_ == -1 || par->balance_ == 1)
                return;

        if (par->balance_ == 2) {
            if (par->right_->balance_ == -1)
                par = LBRotate(par);
            else par = LLRotate(par);
        }

        else if (par->balance_ == -2) {
            if (par->left_->balance_ == 1)
                par = RBRotate(par);
            else par = RLRotate(par);
        }

        else par = par->parent_;
    }
}

template<typename ValueType, class Compare>
void AVLSet<ValueType, Compare>::HBRecalc(AVLSet::Item *par) {

    if (par->left_ == nullptr && par->right_ == nullptr) {
        par->balance_ = 0;
        par->height_ = 1;
    }

    else if (par->left_ == nullptr) {
        par->balance_ = par->right_->height_;
        par->height_ = par->right_->height_ + 1;
    }

    else if (par->right_ == nullptr) {
        par->balance_ = -1 * par->left_->height_;
        par->height_ = par->left_->height_ + 1;
    }

    else {
        par->balance_ = par->right_->height_ - par->left_->height_;
        par->height_ = (par->right_->height_ > par->left_->height_ ?
                        par->right_->height_ : par->left_->height_) + 1;
    }
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::Item *AVLSet<ValueType, Compare>::LLRotate(Item *par) {
    Item *p_l = par->left_;
    Item *p_r = par->right_;
    Item *p_r_left = p_r->left_;
    Item *p_r_right = p_r->right_;

    if (root_ == par)
        root_ = p_r;

    par->right_ = p_r_left;
    if (p_r_left != nullptr)
        p_r_left->parent_ = par;

    p_r->parent_ = par->parent_;
    if (p_r->parent_ != nullptr) {
        if (Comp(p_r->key_, p_r->parent_->key_))
            p_r->parent_->left_ = p_r;
        else p_r->parent_->right_ = p_r;
    }
    p_r->left_ = par;
    par->parent_ = p_r;

    par->height_ = (p_r_left != nullptr ? p_r_left->height_ : 0) + 1;
    par->balance_ = par->height_ - 1;
    if (p_l != nullptr) {
        if (p_l->height_ >= par->height_)
            par->height_ = p_l->height_ + 1;
        par->balance_ -= p_l->height_;
    }

    p_r->height_ = (p_r_right != nullptr ? p_r_right->height_ : 0) + 1;
    p_r->balance_ = p_r->height_ - 1;
    if (par->height_ >= p_r->height_)
        p_r->height_ = par->height_ + 1;
    p_r->balance_ -= par->height_;

    return p_r->parent_;
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::Item *AVLSet<ValueType, Compare>::LBRotate(Item *par) {
    Item *p_l = par->left_;
    Item *p_r = par->right_;
    Item *p_r_left = p_r->left_;
    Item *p_r_right = p_r->right_;
    Item *p_r_left_l = p_r_left->left_;
    Item *p_r_left_r = p_r_left->right_;

    if (root_ == par)
        root_ = p_r_left;

    par->right_ = p_r_left_l;
    if (p_r_left_l != nullptr)
        p_r_left_l->parent_ = par;
    p_r->left_ = p_r_left_r;
    if (p_r_left_r != nullptr)
        p_r_left_r->parent_ = p_r;

    p_r_left->parent_ = par->parent_;
    if (p_r_left->parent_ != nullptr) {
        if (Comp(p_r_left->key_, p_r_left->parent_->key_))
            p_r_left->parent_->left_ = p_r_left;
        else p_r_left->parent_->right_ = p_r_left;
    }
    p_r_left->left_ = par;
    par->parent_ = p_r_left;
    p_r_left->right_ = p_r;
    p_r->parent_ = p_r_left;

    par->height_ = (p_r_left_l != nullptr ? p_r_left_l->height_ : 0) + 1;
    par->balance_ = par->height_ - 1;
    if (p_l != nullptr) {
        if (p_l->height_ >= par->height_)
            par->height_ = p_l->height_ + 1;
        par->balance_ -= p_l->height_;
    }

    p_r->height_ = (p_r_right != nullptr ? p_r_right->height_ : 0) + 1;
    p_r->balance_ = p_r->height_ - 1;
    if (p_r_left_r != nullptr) {
        if (p_r_left_r->height_ >= p_r->height_)
            p_r->height_ = p_r_left_r->height_ + 1;
        p_r->balance_ -= p_r_left_r->height_;
    }

    p_r_left->height_ = (par->height_ > p_r->height_ ? par->height_ : p_r->height_) + 1;
    p_r_left->balance_ = p_r->height_ - par->height_;

    return p_r_left->parent_;
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::Item *AVLSet<ValueType, Compare>::RLRotate(Item *par) {
    Item *p_l = par->left_;
    Item *p_r = par->right_;
    Item *p_l_left = p_l->left_;
    Item *p_l_right = p_l->right_;

    if (root_ == par)
        root_ = p_l;

    par->left_ = p_l_right;
    if (p_l_right != nullptr)
        p_l_right->parent_ = par;

    p_l->parent_ = par->parent_;
    if (p_l->parent_ != nullptr) {
        if (Comp(p_l->key_, p_l->parent_->key_))
            p_l->parent_->left_ = p_l;
        else p_l->parent_->right_ = p_l;
    }
    p_l->right_ = par;
    par->parent_ = p_l;

    par->height_ = (p_r != nullptr ? p_r->height_ : 0) + 1;
    par->balance_ = par->height_ - 1;
    if (p_l_right != nullptr) {
        if (p_l_right->height_ >= par->height_)
            par->height_ = p_l_right->height_ + 1;
        par->balance_ -= p_l_right->height_;
    }

    p_l->height_ = par->height_ + 1;
    p_l->balance_ = p_l->height_ - 1;
    if (p_l_left != nullptr) {
        if (p_l_left->height_ >= p_l->height_)
            p_l->height_ = p_l_left->height_ + 1;
        p_l->balance_ -= p_l_left->height_;
    }

    return p_l->parent_;
}

template<typename ValueType, class Compare>
typename AVLSet<ValueType, Compare>::Item *AVLSet<ValueType, Compare>::RBRotate(Item *par) {
    Item *p_l = par->left_;
    Item *p_r = par->right_;
    Item *p_l_left = p_l->left_;
    Item *p_l_right = p_l->right_;
    Item *p_l_right_l = p_l_right->left_;
    Item *p_l_right_r = p_l_right->right_;

    if (root_ == par)
        root_ = p_l_right;

    p_l->right_ = p_l_right_l;
    if (p_l_right_l != nullptr)
        p_l_right_l->parent_ = p_l;
    par->left_ = p_l_right_r;
    if (p_l_right_r != nullptr)
        p_l_right_r->parent_ = par;

    p_l_right->parent_ = par->parent_;
    if (p_l_right->parent_ != nullptr) {
        if (Comp(p_l_right->key_, p_l_right->parent_->key_))
            p_l_right->parent_->left_ = p_l_right;
        else p_l_right->parent_->right_ = p_l_right;
    }

    p_l_right->left_ = p_l;
    p_l->parent_ = p_l_right;
    p_l_right->right_ = par;
    par->parent_ = p_l_right;

    p_l->height_ = (p_l_right_l != nullptr ? p_l_right_l->height_ : 0) + 1;
    p_l->balance_ = p_l->height_ - 1;
    if (p_l_left != nullptr) {
        if (p_l_left->height_ >= p_l->height_)
            p_l->height_ = p_l_left->height_ + 1;
        p_l->balance_ -= p_l_left->height_;
    }

    par->height_ = (p_r != nullptr ? p_r->height_ : 0) + 1;
    par->balance_ = par->height_ - 1;
    if (p_l_right_r != nullptr) {
        if (p_l_right_r->height_ >= par->height_)
            par->height_ = p_l_right_r->height_ + 1;
        par->balance_ -= p_l_right_r->height_;
    }

    p_l_right->height_ = (par->height_ > p_l->height_ ? par->height_ : p_l->height_) + 1;
    p_l_right->balance_ = par->height_ - p_l->height_;

    return p_l_right->parent_;
}

#endif //PROGTASKSCPP_MY_AVL_SET_H
