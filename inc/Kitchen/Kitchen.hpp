/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** Kitchen
*/

#pragma once
#include "ThreadPool.hpp"
#include  <unordered_map>
#include "tools.hpp"
#include "Pizza.hpp"
#include "Message.hpp"
#include "Processes.hpp"
#include <unordered_map>

namespace plazza {

        enum Ingre {
        doe,
        tomato,
        gruyere,
        ham,
        mushrooms,
        eggplant,
        steak,
        goatchees,
        chieffove,
    };

    const std::unordered_map<plazza::PizzaType, uint16_t> PizzaTime = {
        {plazza::PizzaType::Margarita, 1000},
        {plazza::PizzaType::Regina, 2000},
        {plazza::PizzaType::Americana, 2000},
        {plazza::PizzaType::Fantasia, 4000}
    };


    const std::vector<Ingre> MargaritaIngre = {
        Ingre::doe,
        Ingre::tomato,
        Ingre::gruyere
    };

    const std::vector<Ingre> ReginaIngre = {
        Ingre::doe,
        Ingre::tomato,
        Ingre::gruyere,
        Ingre::ham,
        Ingre::mushrooms
    };

    const std::vector<Ingre> AmericanaIngre = {
        Ingre::doe,
        Ingre::tomato,
        Ingre::gruyere,
        Ingre::steak
    };

    const std::vector<Ingre> FantasiaIngre = {
        Ingre::doe,
        Ingre::tomato,
        Ingre::eggplant,
        Ingre::goatchees,
        Ingre::chieffove
    };

    const std::unordered_map<plazza::PizzaType, std::vector<Ingre>> PizzaIngreMap = {
        {plazza::PizzaType::Margarita, MargaritaIngre},
        {plazza::PizzaType::Regina, ReginaIngre},
        {plazza::PizzaType::Americana, AmericanaIngre},
        {plazza::PizzaType::Fantasia, FantasiaIngre}
    };


    class Kitchen : public ThreadPool, public IProgram {
        private:
            std::unordered_map<Ingre, std::atomic<uint16_t>> stockMap;
            /* = {
            {Ingre::doe,         5},
            {Ingre::tomato,      5},
            {Ingre::gruyere,     5},
            {Ingre::ham,         5},
            {Ingre::mushrooms,   5},
            {Ingre::eggplant,    5},
            {Ingre::goatchees,   5},
            {Ingre::chieffove,   5},
        };*/
        public:
           explicit Kitchen(const std::string &inPath, const std::string &outPath);
            Kitchen() = delete;

            std::string status();

            void cook(Pizza pizza);

            void execute();

            void handleCommands(const std::string &command);

        private:
            std::mutex m_stock;
            std::pair<In, Out> msg;
            std::condition_variable someStorageEmptied;
    };
}
