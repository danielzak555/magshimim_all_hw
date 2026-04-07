#pragma once

#include <string>
#include "UserList.h"
#include "Page.h"
#include "User.h"

class Profile
{
private:

    User own;
    Page page;
	UserList friends;

public:
    void init(User owner);
    std::string getFriendsWithSameNameLength() const;
    std::string getFriends() const;
    std::string getPage() const;
    User getOwner() const;

    void addFriend(User friend_to_add);
    void addPostToProfilePage(const std::string& post);
    void setStatus(const std::string& new_status);

    void clear();

    void changeAllWordsInStatus(const std::string& word);
    void changeWordInStatus(const std::string& word_to_replace, const std::string& new_word);

};
