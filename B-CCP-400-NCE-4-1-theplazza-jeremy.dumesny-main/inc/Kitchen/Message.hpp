/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** Message
*/

#pragma once
#include <cerrno>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

class NamePipe {
    public:
        NamePipe(const std::string &path) : _path(path) {}
        virtual ~NamePipe() = default;
        protected:
        std::string _path;
};

class In : public NamePipe {
    public:

        In(const std::string &path) : NamePipe(path){}
        void init() {
            if (access(_path.c_str(), R_OK) == -1) {
                if (mkfifo(_path.c_str(), 0644) == -1)
                    if (errno != EEXIST)
                        throw std::runtime_error(std::string("NamedPipe::In ") + strerror(errno) + _path);
            }

            _stream.open(_path);

            if (_stream.fail())
                throw std::runtime_error("Couldn't open named pipe.");
        }

        ~In() {
            _stream.close();
            unlink(_path.c_str());
        }

        In &operator>>(std::string &);

        void recv(std::string &);

    private:
        std::ifstream _stream;
};

class Out : public NamePipe {
    public:
        Out(const std::string &path) : NamePipe(path){}
        void init() {
            if (access(_path.c_str(), W_OK) == -1) {
                if (mkfifo(_path.c_str(), 0644) == -1)
                    if (errno != EEXIST)
                        throw std::runtime_error(std::string("NamedPipe::Out ") + strerror(errno));
            }

            _stream.open(_path);

            if (_stream.fail())
                throw std::runtime_error("Couldn't open named pipe.");
        }

        ~Out() {
            _stream.close();
            unlink(_path.c_str());
        }

        Out &operator<<(std::string const &);

        void send(std::string const &);

    private:
        std::ofstream _stream;
};