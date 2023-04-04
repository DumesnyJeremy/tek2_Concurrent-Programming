/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** Pizza
*/

#pragma once

#include <string>
#include <unordered_map>

namespace plazza {
    enum PizzaType {
            Regina = 1,
            Margarita = 2,
            Americana = 4,
            Fantasia = 8
    };
    enum PizzaSize {
            S = 1,
            M = 2,
            L = 4,
            XL = 8,
            XXL = 16
    };

    const std::unordered_map<std::string, PizzaSize> PizzaSizeList = {/* NOLINT */
            {"S",   PizzaSize::S},
            {"M",   PizzaSize::M},
            {"L",   PizzaSize::L},
            {"XL",  PizzaSize::XL},
            {"XXL", PizzaSize::XXL}
    };

    const std::unordered_map<std::string, plazza::PizzaType> PizzaTypeList = { /* NOLINT */
            {"regina",    PizzaType::Regina},
            {"margarita", PizzaType::Margarita},
            {"americana", PizzaType::Americana},
            {"fantasia",  PizzaType::Fantasia}
    };

    const std::unordered_map<PizzaSize, std::string> PizzaSizeEumList = {/* NOLINT */
            {PizzaSize::S, "S"},
            {PizzaSize::M, "M"},
            {PizzaSize::L, "L"},
            {PizzaSize::XL, "XL"},
            {PizzaSize::XXL, "XXL"}
    };

    const std::unordered_map<plazza::PizzaType, std::string> PizzaTypeEumList = { /* NOLINT */
            {PizzaType::Regina, "regina"},
            {PizzaType::Margarita, "margarita"},
            {PizzaType::Americana, "americana"},
            {PizzaType::Fantasia, "fantasia"}
    };

    class Pizza {
        private:
            PizzaType _pizzaType;
            PizzaSize _pizzaSize;
            std::string _pizzaTypeString;
            std::string _pizzaSizeString;
        public:
            Pizza(const std::string &pizzaType, const std::string &pizzaSize);

            [[nodiscard]] const PizzaType &getPizzaTypeEnum() const;

            [[nodiscard]] const PizzaSize &getPizzaSizeEnum() const;

            [[nodiscard]] const std::string &getPizzaTypeString() const;

            [[nodiscard]] const std::string &getPizzaSizeString() const;

            static bool isValid(const std::string &type, const std::string &size) noexcept;
    
            friend std::ostream& operator<<(std::ostream& out, Pizza& pizza) {
                out << std::string("pizza: ") << pizza._pizzaTypeString << std::string(" size: ") << pizza._pizzaSizeString;
                return out;
            };
    };
}// namespace plazza
