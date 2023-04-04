/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** Message
*/

#include "Message.hpp"

In &In::operator>>(std::string &str) {
    if (_stream.good())
        std::getline(_stream, str);

    return *this;
}

void In::recv(std::string &str) {
    this->operator>>(str);
}

Out &Out::operator<<(std::string const &str) {
    if (_stream.good())
        _stream << str << std::endl;

    return *this;
}

void Out::send(std::string const &str) {
    this->operator<<(str);
}