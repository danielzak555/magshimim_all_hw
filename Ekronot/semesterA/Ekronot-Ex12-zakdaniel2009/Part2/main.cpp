#include "MessageSender.h"

int main() {
    MessageSender sender;
    
    std::thread adminThread(&MessageSender::readAdminFile, &sender);
    std::thread writerThread(&MessageSender::writeMessagesToUsersFile, &sender);
    
    sender.showMenu();
    
    if (adminThread.joinable()) adminThread.join();
    if (writerThread.joinable()) writerThread.join();

    std::cout << "All threads stopped. Goodbye!\n";
    return 0;
}