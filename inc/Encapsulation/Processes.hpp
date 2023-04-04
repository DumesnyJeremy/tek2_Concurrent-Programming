/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** Processes
*/

#pragma once
#include <csignal>
#include <cstring>
#include <errno.h>
#include <stdexcept>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

class IProgram {
    public:
        virtual ~IProgram() {};
        virtual void execute() = 0;
};

class Processes {
public:
    class Exception : public std::runtime_error {
        public:
            template<typename T>
            explicit Exception(T &&msg) : std::runtime_error(msg), _msg(std::forward<T>(msg)){};
            virtual ~Exception() throw(){};
            [[nodiscard]] const char *what() const noexcept final { return _msg.data(); }

        protected:
            std::string _msg;
    };

public:
    enum class Status { RUNNING, STOPPED };
    Processes(IProgram &);

    ~Processes() {
        this->wait();
    }

    bool kill(int killCode = SIGTERM);

    void wait();

private:
    pid_t _pid;
    Status _status;
};
