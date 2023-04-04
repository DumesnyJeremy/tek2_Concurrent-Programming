/*
** EPITECH PROJECT, 2021
** NanoTekSpice [WSL: Ubuntu]
** File description:
** Errors
*/

#include "Errors.hpp"
#include <string>

std::string const &PlazzaError::getComponent() const
{
    return _component;
}

const char *PlazzaError::what() const noexcept
{
    return _message.data();
}
/*
ParserNtsError::ParserNtsError(std::string const &message, std::string const &component)
: PlazzaError(message, component)
{
}

SyntaxError::SyntaxError(std::string const &message, std::string const &component)
: PlazzaError(message, component)
{
}

ChipsetError::ChipsetError(std::string const &message, std::string const &component)
: PlazzaError(message, component)
{
}
*/