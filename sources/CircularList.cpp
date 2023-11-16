#include "../headers/CircularList.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;
/*
template<typename type_t>
typename CircularList<type_t>::iterator& CircularList<type_t>::iterator::operator++() {
    ++this->it;
    if(this->it == circularListPtr->list.end())
        this->it = circularListPtr->list.begin();

    return *this;
}

template<typename type_t>
type_t& CircularList<type_t>::iterator::operator*() {
    return *it;
}

template<typename type_t>
bool CircularList<type_t>::iterator::operator!=(const typename CircularList<type_t>::iterator& other) const {
    return it != other.it;
}

template<typename type_t>
bool CircularList<type_t>::iterator::operator==(const typename CircularList<type_t>::iterator& other) const {
    return it == other.it;
}

template<typename type_t>
void CircularList<type_t>::push_back(const type_t &value) {
    list.push_back(value);
}

template<typename type_t>
void CircularList<type_t>::pop_back() {
    if(!list.empty())
        list.pop_back();
    else
        std::cerr << "The list is already empty !";
}

template<typename type_t>
typename CircularList<type_t>::iterator CircularList<type_t>::begin() const {
    return iterator(list.begin(), this);
}

template <typename type_t>
typename CircularList<type_t>::iterator CircularList<type_t>::end() const {
    return iterator(list.end(), this);
}
*/
/*
template<typename type_t>
void CircularList<type_t>::iterator::operator++(int) {
    ++this->it;
    if(this->it == circularListPtr->list.end())
        this->it = circularListPtr->list.begin();
}*/