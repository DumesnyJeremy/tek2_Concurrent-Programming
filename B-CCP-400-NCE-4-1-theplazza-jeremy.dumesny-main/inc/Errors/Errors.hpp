/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** Errors
*/

#pragma once

#include <exception>
#include <stdexcept>
#include <string>
//#include <concepts>
//#include <type_traits>
//template <typename T>
//concept String = requires(T type) {
//    {std::string(std::forward<T>(type))} -> std::convertible_to<std::string>;
//};

class PlazzaError : public std::exception {
  public:
    template<typename T>
    explicit PlazzaError(T &&message, T &&component = "Unknown")
        :_message(std::forward<T>(message)), _component(std::forward<T>(component))
    {
    }
    virtual ~PlazzaError() throw() {}
    [[nodiscard]] std::string const &getComponent() const;
    [[nodiscard]] const char *what() const noexcept final;

  private:
    std::string _message;
    std::string _component;
};
/*
class ChipsetError : public PlazzaError {
  public:
    ~ChipsetError() throw() {}
};

class ParserNtsError : public PlazzaError {
  public:
    ~ParserNtsError() throw() {}
};

class SyntaxError : public PlazzaError {
  public:
    ~SyntaxError() throw() {}
};
*/