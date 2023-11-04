//
// Created by je_gi on 2023-11-04.
//

#ifndef OOP_CIRCULARLIST_HPP
#define OOP_CIRCULARLIST_HPP

#include <list>

template<typename type_t>
class CircularList {
    std::list<type_t> list;
    std::list<type_t>::iterator it;
public:
    CircularList() = delete;
    ~CircularList() = default;
    type_t getCurrentElement() const noexcept;
    CircularList<type_t>& pointToNextElement();
    CircularList<type_t>& removeCurrentElement();
    CircularList<type_t>& pushbackElement(type_t element);
};

#endif //OOP_CIRCULARLIST_HPP
