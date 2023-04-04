/*
** EPITECH PROJECT, 2021
** plazza
** File description:
** Orders
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <regex>
#include "Errors.hpp"
#include "Orders.hpp"
#include "tools.hpp"

std::string remove_extra_ws_mute(std::string s)
{
    s.erase(std::unique(std::begin(s), std::end(s), [](unsigned char a, unsigned char b){
        return std::isspace(a) && std::isspace(b);
    }), std::end(s));
    if (s[0] == ' ')
        return std::string(s, 1);
    return s;
}

std::vector<std::string> tokenize(const std::string &str, std::string &&del, std::vector<std::string> &out) {
    size_t start;
    size_t end = 0;
    std::string noExtraSpace;

    while ((start = str.find_first_not_of(del, end)) != std::string::npos) {
        end = str.find(del, start);
        out.push_back(remove_extra_ws_mute(str.substr(start, end - start)));
    }
    return out;
}

plazza::Orders::Orders(const std::string &listOrders) {
    this->add(listOrders);
}

plazza::Orders::~Orders() {
}

bool plazza::Orders::isValid(std::string &order) noexcept {
    if (!std::regex_match(order, std::regex("([a-z|A-Z]+) (S|M|L|XL|XXL) x([1-9][0-9]*)"))) {
        std::cerr << RED << "⚠ order: " << CYAN << "\"" << order << "\"" << RESET <<" is not valid." << std::endl
                  << "this group of orders will be ignored!" << std::endl;
        return false;
    }
    return true;
}

void plazza::Orders::add(const std::string &listOrders)
{
    std::vector<std::string> lists, list;
    tokenize(listOrders, ";", lists);

    for (auto &order: lists) {
        if (!isValid(order)) continue;
        tokenize(order, " ", list);
        std::transform(list[0].begin(), list[0].end(),
                       list[0].begin(), ::tolower);

        if (Pizza::isValid(list[0], list[1])) {
            for (auto i = 0; i < std::atoi(&(list[2][1])); i++) {
                _pizzas.emplace(list[0], list[1]);
            }
        }
        list.clear();
    }
}