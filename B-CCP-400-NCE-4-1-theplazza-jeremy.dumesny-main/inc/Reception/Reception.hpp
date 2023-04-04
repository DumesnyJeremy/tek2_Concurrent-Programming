/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** Reception
*/

#pragma once

#include "Manager.hpp"
#include "Orders.hpp"
#include <fcntl.h>
#include <iostream>
#include <memory>
#include <mutex>
#include <sys/stat.h>
#include <sys/types.h>
#include <unordered_map>
#include <list>

namespace plazza {
    class Reception {
    public:
        [[noreturn]] Reception();

        ~Reception();

    private:
        Manager _kitchenManager;

    private:
        // getters
        void getStatus() const;

        void formatOrders();

        // commands
        void checkInput(const std::string &buf);

        void exit();

        // tools
        void manageUsrOrders(const std::string &buf);

    void openKitchen();

        using pipe = std::pair<std::unique_ptr<In>, std::unique_ptr<Out>>;
        uint32_t _cout = 0;
        std::list<pipe> _kitchensMsg;
        Orders _orders;
        std::unique_ptr<Processes> _processes;
        std::mutex _mutex;
    };
}// namespace plazza