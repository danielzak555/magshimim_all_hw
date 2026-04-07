#pragma once

#include <string>

class Page
{
private:

    std::string status;
    std::string posts;

public:
    void init();
    std::string getStatus() const ;
    std::string getPosts() const ;
    
    void addLineToPosts(const std::string& new_line);
    void setStatus(const std::string& status);

    void clearPage();
};
