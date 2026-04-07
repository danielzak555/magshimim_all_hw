#pragma once

#include <string>
#include <set>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <fstream>
#include <queue>
#include <atomic>

class MessageSender {
public:
    MessageSender() : running(true) {}
    ~MessageSender() { stop(); }

    void showMenu();
    void signIn();
    void signOut();
    void showConnectedUsers() const;

    void readAdminFile();
    void writeMessagesToUsersFile();
    
    void stop();
    bool isRunning() const { return running; }

private:
    std::set<std::string> users;
    mutable std::mutex usersMtx;
    
    std::queue<std::string> messageQueue;
    std::mutex queueMtx;
    std::condition_variable queueCV;
    
    std::atomic<bool> running;
};