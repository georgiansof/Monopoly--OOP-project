#include "../headers/Property.hpp"

[[nodiscard]] uint32_t Property::getPrice() const noexcept {
    return this->price;
}