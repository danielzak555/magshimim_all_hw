#include "MessageSender.h"

void MessageSender::stop() {
    running = false;
    queueCV.notify_all();
}

void MessageSender::showMenu() {
    while (running) {
        std::cout << "1. Sign In\n";
        std::cout << "2. Sign Out\n";
        std::cout << "3. Connected Users\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number (1-4).\n";
            continue;
        }

        switch (choice) {
            case 1:
                try {
                    signIn();
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what();
                }
                break;
            case 2:
                try {
                    signOut();
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what();
                }
                break;
            case 3:
                showConnectedUsers();
                break;
            case 4:
                std::cout << "Exiting...\n";
                stop();
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

void MessageSender::signIn() {
    std::string username;
    std::cout << "Enter username to sign in: ";
    std::cin >> username;

    std::lock_guard<std::mutex> lock(usersMtx);
    auto result = users.insert(username);
    if (result.second) {
        std::cout << username << " signed in successfully.\n";
    } else {
        throw std::invalid_argument(username + " is already signed in.\n");
    }
}

void MessageSender::signOut() {
    std::string username;
    std::cout << "Enter username to sign out: ";
    std::cin >> username;

    std::lock_guard<std::mutex> lock(usersMtx);
    if (users.erase(username) > 0) {
        std::cout << username << " signed out successfully.\n";
    } else {
        throw std::invalid_argument(username + " is not signed in.\n");
    }
}

void MessageSender::showConnectedUsers() const {
    std::lock_guard<std::mutex> lock(usersMtx);
    if (users.empty()) {
        std::cout << "No users connected.\n";
        return;
    }

    std::cout << "Connected users:\n";
    for (const auto& user : users) {
        std::cout << "  - " << user << "\n";
    }
}

void MessageSender::readAdminFile() {

    std::ofstream createFile("data.txt", std::ios::app);
    createFile.close();
    
    while (running) {
        try {
            std::ifstream file("data.txt");
            if (file.is_open()) {
                std::string line;
                bool hasNewMessages = false;
                
                {
                    std::lock_guard<std::mutex> lock(queueMtx);
                    while (std::getline(file, line)) {
                        if (!line.empty()) {
                            messageQueue.push(line);
                            hasNewMessages = true;
                        }
                    }
                }
                file.close();

                if (hasNewMessages) {
                    queueCV.notify_one();  // Notify writer thread
                    // Clear the file after reading
                    std::ofstream out("data.txt", std::ios::trunc);
                    out.close();
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error reading admin file: " << e.what() << "\n";
        }

        for (int i = 0; i < 10 && running; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void MessageSender::writeMessagesToUsersFile() {
    while (running) {
        std::string message;
        
        std::unique_lock<std::mutex> lock(queueMtx);
        // Wait until queue has messages OR we are stopping
        queueCV.wait(lock, [this] { 
            return !messageQueue.empty() || !running; 
        });
        
        if (!running && messageQueue.empty()) {
            break;
        }
        
        if (!messageQueue.empty()) {
            message = messageQueue.front();
            messageQueue.pop();
        }
        
        if (!message.empty()) {
            std::set<std::string> currentUsers;
            {
                std::lock_guard<std::mutex> lock(usersMtx);
                currentUsers = users;
            }
            
            std::ofstream file("output.txt", std::ios::app);
            if (file.is_open()) {
                for (const auto& user : currentUsers) {
                    file << user << ": " << message << "\n";
                }
            } else {
                std::cout << "Could not open output file\n";
            }
        }
    }
}