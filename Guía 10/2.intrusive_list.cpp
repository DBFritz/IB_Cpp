#include <iostream>
#include <iterator>

namespace intrusive{
    template <typename T>
    class node;

    template <typename T>
    class list;

    //template <typename T>
    //class iterator;
}

template <typename T>
class intrusive::node
{
    template <typename S, node<S> S::*> friend class intrusive::list;
    template <typename S, node<S> S::*> friend class intrusive::iterator;

    T*       next;
    node<T>* prev;
public:
    node(): next(), prev() {}
    node(node const&) {}
    void operator=(node const&) {}
};

template <typename T, intrusive::node<T> T::*Link>
class intrusive::iterator
{
    template <typename S, node<S> S::*> friend class intrusive::list;
    node<T>* current;

public:
    explicit iterator(node<T>* current): current(current) {}
    T& operator*() { return *this->operator->(); }
    T* operator->() { return this->current->next; }
    bool operator== (iterator const& other) const {
        return this->current == other.current;
    }
    bool operator!= (iterator const& other) const {
        return !(*this == other);
    }
    iterator& operator++() {
        this->current = &(this->current->next->*Link);
        return *this;
    }
    iterator operator++(int) {
        iterator rc(*this);
        this->operator++();
        return rc;
    }
    iterator& operator--() {
        this->current = this->current->prev;
        return *this;
    }
    iterator operator--(int) {
        iterator rc(*this);
        this->operator--();
        return rc;
    }
};

template <typename T, intrusive::node<T> T::*Link>
class intrusive::list
{
    node<T> content;

public:
    list() { this->content.prev = &this->content; }
    iterator<T, Link> begin() { return iterator<T, Link>(&this->content); }
    iterator<T, Link> end() { return iterator<T, Link>(this->content.prev); }

    T& front() { return *this->content.next; }
    T& back() { return *(this->content.prev->prev->next); }
    bool empty() const { return &this->content == this->content.prev; }
    void push_back(T& node) { this->insert(this->end(), node); }
    void push_front(T& node) { this->insert(this->begin(), node); }
    void insert(iterator<T, Link> pos, T& node) {
        (node.*Link).next = pos.current->next;
        ((node.*Link).next
         ? (pos.current->next->*Link).prev 
         : this->content.prev) = &(node.*Link);
        (node.*Link).prev = pos.current;
        pos.current->next = &node;
    }
    iterator<T, Link> erase(iterator<T, Link> it) {
        it.current->next = (it.current->next->*Link).next;
        (it.current->next
         ? (it.current->next->*Link).prev
         : this->content.prev) = it.current;
        return iterator<T, Link>(&(it.current->next->*Link));
    }
};

template <typename T, intrusive::node<T> T::*Link>
std::ostream& intrusive::operator<< (std::ostream& out, intrusive::list<T, Link>& list)
{
    out << "[";
    if (!list.empty()) {
        std::copy(list.begin(), --list.end(), std::ostream_iterator<T>(out, ", "));
        out << list.back();
    }
    return out << "]";
}

class Node {
public:
    intrusive::node<Node> link0;
    intrusive::node<Node> link1;
    int                   n;
    Node(int n): n(n) {}
};
std::ostream& operator<< (std::ostream& out, Node const& n) {
    return out << n.n;
}
