/*
** EPITECH PROJECT, 2021
** plazza [WSL: Ubuntu]
** File description:
** ThreadPool
*/

#include "ThreadPool.hpp"
#include <iostream>

ThreadPool::ThreadPool(uint16_t numThreads) :_stoped{ false }, _idlThrNum{ numThreads }
{
}

ThreadPool::~ThreadPool()
{
    _stoped.store(true);
    cv_task.notify_all(); // 唤醒所有线程执行 - Wake up all threads to execute
    for (std::thread& thread : _threads) {
        //thread.detach(); // 让线程“自生自灭”  Leave threads "to their own devices"
        if(thread.joinable())
            thread.join(); // 等待任务结束， 前提：线程一定会执行完 - Wait for the task to finish, premise: the thread must finish executing
    }
}

void ThreadPool::start() {
    std::cout << "itialize the thread pool" << std::endl;
    for (uint16_t i = 0; i < _idlThrNum; ++i) {   //初始化线程数量 Initialize of threads
        _threads.emplace_back(
            [this] { // 工作线程函数 Worker thread function
                threadsStatusMap[std::this_thread::get_id()] = STARTED;
                while(!_stoped) {
                    Task task;

                    {   // 获取一个待执行的 task Gets a task to be executed
                        std::unique_lock<std::mutex> lock{ _m_lock };// unique_lock 相比 lock_guard 的好处是：可以随时 unlock() 和 lock()
                                                                     // The advantage of unique_lock over lock_guard is that it can be unlocked() and locked() at any time.
                        cv_task.wait(lock,
                            [this] {
                                return _stoped.load() || !_tasks.empty();
                            }
                        ); // wait 直到有 task Wait until there is a task
                        if (_stoped && _tasks.empty())
                            return;
                        task = std::move(_tasks.front()); // 取一个 task - Get one task
                        _tasks.pop();
                    }
                    _idlThrNum--;
                    threadsStatusMap[std::this_thread::get_id()] = RUNING;
                    task(); // start execute task;
                    threadsStatusMap[std::this_thread::get_id()] = STARTED;
                    _idlThrNum++;
                }
            }
        );
    }
}