/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** Processes
*/

#include "Processes.hpp"

Processes::Processes(IProgram &program) : _pid(0), _status(Status::STOPPED) {
    if ((_pid = fork()) == -1)
        throw Processes::Exception(std::string("fork: ") + strerror(errno));

    if (_pid == 0) {
        try {
            program.execute();
            exit(0);
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
            exit(84);
        }
    } else {
        _status = Status::RUNNING;
    }
}

bool Processes::kill(int killCode) {
    try {
        ::kill(_pid, killCode);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

void Processes::wait() {
    if (_status == Status::RUNNING) {
        if (waitpid(_pid, NULL, 0) == -1)
            throw Processes::Exception(std::string("waitpid: ") + strerror(errno));
        _status = Status::STOPPED;
    }
}
