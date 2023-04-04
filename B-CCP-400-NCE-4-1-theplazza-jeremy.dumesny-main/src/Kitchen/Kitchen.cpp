/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include <iostream>
#include "tools.hpp"
#include "ThreadSave.hpp"

plazza::Kitchen::Kitchen(const std::string &inPath, const std::string &outPath) : ThreadPool(plazza::cooks), msg(inPath, outPath)
{
    stockMap[Ingre::doe]            = 5;
    stockMap[Ingre::tomato]         = 5;
    stockMap[Ingre::gruyere]        = 5;
    stockMap[Ingre::ham]            = 5;
    stockMap[Ingre::mushrooms]      = 5;
    stockMap[Ingre::eggplant]       = 5;
    stockMap[Ingre::goatchees]      = 5;
    stockMap[Ingre::chieffove]      = 5;
}

std::string plazza::Kitchen::status()
{
    std::string s;
    for (uint16_t i = 0; i < plazza::cooks; ++i) {
        if (get_status(i) == Status::RUNING) {
            s += std::string("cook num: " + std::to_string(i) + " is still cooking\n");
        } else {
            s += std::string("cook num: " + std::to_string(i) + " is free\n");
        }
    }
    return s;
}

void plazza::Kitchen::cook(Pizza pizza) {
    float time = PizzaTime.at(pizza.getPizzaTypeEnum()) * cookTime;
    auto &ingres = PizzaIngreMap.at(pizza.getPizzaTypeEnum());
    for (auto &ingre : ingres) {
        std::unique_lock<std::mutex> lock{m_stock};
        while (stockMap.at(ingre) == 0) {
            ThreadSafe::cout() << "cook id: " << std::this_thread::get_id() << "ingredient for " << pizza  << " not conplecte, perpering" << std::endl;
            someStorageEmptied.wait(lock);
            ThreadSafe::cout() << "cook id: " << std::this_thread::get_id() << " finish perpering" << std::endl;
        }
        stockMap.at(ingre)--;
    }
    ThreadSafe::cout() << "cook start cooking: " << pizza << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(time)));
    ThreadSafe::cout() << "cook finish cook: " << pizza << std::endl;
}

void plazza::Kitchen::handleCommands(const std::string &command)
{
    std::vector<std::string> cmd;
    tokenize(command, "_", cmd);
    if (!cmd.empty() and cmd[0] == "cook") {
        this->commit(std::bind(&plazza::Kitchen::cook, this, Pizza(cmd[1], cmd[2])));
    }
}

void plazza::Kitchen::execute() {
    std::cout << getpid() << std::endl;

    _m_lock.lock();
    msg.second.init();
    _m_lock.unlock();
    _m_lock.lock();
    msg.first.init();
    _m_lock.unlock();
    this->start();
    std::string s;

    std::thread t([this]{
        for (; ;) {
            for (auto &ingre: stockMap) {
                ingre.second++;
            }
            someStorageEmptied.notify_one();
            std::this_thread::sleep_for(std::chrono::milliseconds(plazza::ingredientsTime));
        }
    });

    while (true) {
        msg.first >> s;
        handleCommands(s);
    }
}