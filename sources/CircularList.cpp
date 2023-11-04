#include "../headers/CircularList.hpp"
#include <stdexcept>

using namespace std;

template<typename type_t>
type_t CircularList<type_t>::getCurrentElement() const noexcept {
    if(list.size() > 0)
        return * this->it;
}

template<typename type_t>
CircularList<type_t>& CircularList<type_t>::pointToNextElement() {
    if(list.size() == 0)
        throw std::runtime_error("Trying to get next element in an empty list !");
    if(it != list.end())
        ++it;
    else
        it = list.begin();

    return *this;
}

template<typename type_t>
CircularList<type_t>& CircularList<type_t>::removeCurrentElement() {
    it = list.erase(it);
    return *this;
}

template<typename type_t>
CircularList<type_t>& CircularList<type_t>::pushbackElement(type_t element) {
    list.push_back(element);
    if(list.size() == 1)
        it = list.begin();
    return *this;
}
