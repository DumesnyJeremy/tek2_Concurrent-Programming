/*
** EPITECH PROJECT, 2021
** plazza
** File description:
** Orders
*/

#pragma once

#include <vector>
#include <string>
#include <queue>
#include <Pizza.hpp>
#include "Pizza.hpp"

namespace plazza {

    class Orders {
        public:
            Orders() = default;
            Orders(const std::string &listOrders);

            ~Orders();

            void add(const std::string &listOrders);

            std::queue<plazza::Pizza> _pizzas;

        private:
           [[nodiscard]] bool isValid(std::string &order) noexcept;
    };

}