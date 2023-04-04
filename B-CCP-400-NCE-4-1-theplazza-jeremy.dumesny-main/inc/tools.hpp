/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** tools
*/

#pragma once

#include <cstdint>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define CYAN    "\x1b[36m"
#define MAGENTA "\x1b[35m"
#define RESET   "\x1b[0m"

#include <vector>

std::string remove_extra_ws_mute(std::string s);
std::vector<std::string> tokenize(const std::string &str, std::string &&del, std::vector<std::string> &out);
namespace plazza {
    extern float    cookTime;        // cooking time
    extern std::uint16_t cooks;           // cooks pre kitchen
    extern std::uint16_t ingredientsTime; //
}