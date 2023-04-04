/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** ThreadSaveCout
*/

#pragma once
#include <iostream>
#include <string>
#include <mutex>

namespace ThreadSafe {
    static std::mutex m_CoutMutex;
    struct cout {
        std::unique_lock<std::mutex> m_Lock;
        cout() : m_Lock(std::unique_lock<std::mutex>(m_CoutMutex)) {
        }

        template<typename T>
        cout &operator<<(T &&message) {
            std::cout << std::forward<T>(message);
            return *this;
        }

        cout &operator<<(std::ostream &(*fp)(std::ostream &)) {
            std::cout << fp;
            return *this;
        }
    };
}