//
// Created by je_gi on 2023-11-04.
//

#ifndef OOP_CIRCULARLIST_HPP
#define OOP_CIRCULARLIST_HPP

#include <list>
#include <iostream>

template<typename type_t>
class CircularList {
    std::list<type_t> list;
public:
    CircularList() = default;
    ~CircularList() = default;

    class iterator {
        typename std::list<type_t>::iterator it;
        CircularList<type_t>* circularListPtr;
    public:
        iterator() = default;
        iterator(typename std::list<type_t>::iterator _it,
                 CircularList<type_t> *_circularListPtr)
                 : it(_it), circularListPtr(_circularListPtr) {}
        //void operator++(int); /// clang-tidy conflict if returning const iterator copy

        iterator& operator++() {
            ++this->it;
            if(this->it == circularListPtr->list.end())
                this->it = circularListPtr->list.begin();

            return *this;
        }
        type_t& operator*() {
            return *it;
        }
        bool operator!=(const iterator& other) const {
            return it != other.it;
        }
        bool operator==(const iterator& other) const {
            return it == other.it;
        }
        iterator operator+(int times) {
            iterator newit(*this);
            for(int i = 1; i <= times; ++i)
                ++newit;
            return newit;
        }

    };

    void push_back(const type_t &value) {
        list.push_back(value);
    }

    void pop_back() {
        if(!list.empty())
            list.pop_back();
        else
            std::cerr << "The list is already empty !";
    }

    iterator begin() {
        return iterator(list.begin(), this);
    }

    iterator end() {
        return iterator(list.end(), this);
    }

    [[nodiscard]] int size() const {
        return this->list.size();
    }
};

#endif //OOP_CIRCULARLIST_HPP
