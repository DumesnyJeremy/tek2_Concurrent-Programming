/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** Reception
*/

#include "Reception.hpp"
#include "Kitchen.hpp"
#include "Manager.hpp"
#include "Orders.hpp"
#include "tools.hpp"
#include <memory>
#include <string>
using namespace std::chrono_literals;

plazza::Reception::Reception() {
    std::string buf;
    while (true) {
        std::cout << MAGENTA << "CLIENT: " << RESET;
        std::getline(std::cin, buf);
        checkInput(buf);
    }
}

plazza::Reception::~Reception() {
}

void plazza::Reception::checkInput(const std::string &buf) {
    if (buf == "exit" or std::cin.eof()) {
        this->exit();
    } else if (buf == "status") {
        this->getStatus();
    } else if (!buf.empty()) {
        manageUsrOrders(buf);
    }
}

void plazza::Reception::exit() {
    std::exit(0);
}

void plazza::Reception::getStatus() const {
    // (*_kitchensMsg[0].second) << "hello";
}

void plazza::Reception::openKitchen() {
    if (!_orders._pizzas.empty() and _kitchensMsg.empty()) {
        auto kichenNum = _orders._pizzas.size() > plazza::cooks ? _orders._pizzas.size() / plazza::cooks : 1;
        auto mdl = _orders._pizzas.size() > plazza::cooks ? _orders._pizzas.size() % plazza::cooks : 0;
        auto t = kichenNum + mdl;
        std::mutex m;
        for (size_t i = 0; !_orders._pizzas.empty() and i < t + mdl; ++i) {
            Kitchen tmp("/tmp/k_read_" + std::to_string(_cout), "/tmp/k_out_" + std::to_string(_cout));
            _processes = std::make_unique<Processes>(tmp);

            _kitchensMsg.emplace_back(std::make_unique<In>("/tmp/k_out_" + std::to_string(_cout)), std::make_unique<Out>("/tmp/k_read_" + std::to_string(_cout)));
            _cout++;
            m.lock();
            _kitchensMsg.back().first->init();
            m.unlock();
            m.lock();
            _kitchensMsg.back().second->init();
            m.unlock();
            for (size_t i = 0; !_orders._pizzas.empty() and i < plazza::cooks; i++) {
                std::string type = _orders._pizzas.front().getPizzaTypeString();
                std::string size = _orders._pizzas.front().getPizzaSizeString();
                _orders._pizzas.pop();
                (*_kitchensMsg.back().second) << std::string("cook_" + type + "_" + size);
                if (mdl > 0) {;
                    (*_kitchensMsg.back().second) << std::string("cook_" + type + "_" + size);
                    _orders._pizzas.pop();
                    mdl--;
                }
            }
        }
    }

}

void plazza::Reception::manageUsrOrders(const std::string &buf) {
    _orders.add(buf);
    openKitchen();
    if (!_orders._pizzas.empty()) {
        auto kichenNum = _orders._pizzas.size() > plazza::cooks ? _orders._pizzas.size() / plazza::cooks : 1;
        auto mdl = _orders._pizzas.size() > plazza::cooks ? _orders._pizzas.size() % plazza::cooks : 0;
        auto t = kichenNum + mdl;
        for (size_t i = 0; !_orders._pizzas.empty() and i < t + mdl; ++i) {
            for (size_t i = 0; !_orders._pizzas.empty() and i < plazza::cooks; i++) {
                std::string type = _orders._pizzas.front().getPizzaTypeString();
                std::string size = _orders._pizzas.front().getPizzaSizeString();
                _orders._pizzas.pop();
                (*_kitchensMsg.back().second) << std::string("cook_" + type + "_" + size);
                if (mdl > 0) {;
                    (*_kitchensMsg.back().second) << std::string("cook_" + type + "_" + size);
                    _orders._pizzas.pop();
                    mdl--;
                }
            }
        }
    }
}