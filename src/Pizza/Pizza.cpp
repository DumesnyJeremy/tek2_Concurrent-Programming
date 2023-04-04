/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** Pizza
*/

#include <iostream>
#include "Pizza.hpp"
#include "Errors.hpp"
#include "tools.hpp"

plazza::Pizza::Pizza(const std::string &pizzaType, const std::string &pizzaSize) {
    if (PizzaTypeList.contains(pizzaType)) {
        _pizzaType = PizzaTypeList.at(pizzaType);
        _pizzaTypeString = pizzaType;
    } else
        throw PlazzaError("pizza type: \"" + pizzaType + "\" does not exist");
    if (PizzaSizeList.contains(pizzaSize)) {
        _pizzaSize = PizzaSizeList.at(pizzaSize);
        _pizzaSizeString = pizzaSize;
    } else
        throw PlazzaError("pizza size: \"" + pizzaSize + "\" does not exist");
}

const std::string &plazza::Pizza::getPizzaTypeString() const { return _pizzaTypeString; }

const std::string &plazza::Pizza::getPizzaSizeString() const { return _pizzaSizeString; }

const plazza::PizzaType &plazza::Pizza::getPizzaTypeEnum() const { return _pizzaType; }

const plazza::PizzaSize &plazza::Pizza::getPizzaSizeEnum() const { return _pizzaSize; }

bool plazza::Pizza::isValid(const std::string &type, const std::string &size) noexcept {
    if (!PizzaTypeList.contains(type)) {
        std::cerr << RED << "⚠ pizza type: " << CYAN << "\"" << type << "\"" << RESET << " does not exist" << std::endl;
        return false;
    }
    if (!PizzaSizeList.contains(size)) {
        std::cerr << RED << "⚠ pizza size: " << CYAN << "\"" << size << "\"" << RESET << " does not exist" << std::endl;
        return false;
    }
    return true;
}
