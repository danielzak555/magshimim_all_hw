#include "Profile.h"

void Profile::init(User owner) {
    this->own = owner;
    this->page.init();
    this->friends.init();
}

std::string Profile::getFriendsWithSameNameLength() const {
    int owner_name_length = this->own.getUserName().length();
    std::string result = "";
    UserNode* current = this->friends.get_first();

    while (current != nullptr) {
        User current_user = current->get_data();
        if (current_user.getUserName().length() == owner_name_length) {
            if (!result.empty())
                result += ",";
            result += current_user.getUserName();
        }
        current = current->get_next();
    }

    return result;
}

std::string Profile::getFriends() const {
    std::string result = "";
    UserNode* current = this->friends.get_first();

    while (current != nullptr) {
        User current_user = current->get_data();
        if (!result.empty())
            result += ",";
        result += current_user.getUserName();
        current = current->get_next();
    }

    return result;
}

std::string Profile::getPage() const {
    std::string content = "Status: " + this->page.getStatus() + "\n*******************\n*******************\n" + this->page.getPosts();
    return content;
}

User Profile::getOwner() const {
    return this->own;
}

void Profile::addFriend(User friend_to_add) {
    this->friends.add(friend_to_add);
}

void Profile::addPostToProfilePage(const std::string& post) {
    this->page.addLineToPosts(post);
}

void Profile::setStatus(const std::string& new_status) {
    this->page.setStatus(new_status);
}

void Profile::clear() {
	this->page.clearPage();
	this->friends.clear();
}

void Profile::changeAllWordsInStatus(const std::string& word) {
    bool insideWord = false;
    std::string newStatus = "";
    std::string currentStatus = this->page.getStatus();

    for (int i = 0; i < currentStatus.length(); i++) {
        char c = currentStatus[i];
        if (c == ' ' || c == '\n' || c == '\t') {
            if (insideWord) {
                insideWord = false;
                newStatus += word;
            }
            newStatus += c;
        }
        else {
            insideWord = true;
        }
    }

    if (insideWord) {
        newStatus += word;
    }

    this->page.setStatus(newStatus);
}
void Profile::changeWordInStatus(const std::string& word_to_replace, const std::string& new_word) {
    std::string newStatus = "";
    std::string word = "";
    std::string currentStatus = this->page.getStatus();


    for (int i = 0; i < currentStatus.length(); i++) {
        char c = currentStatus[i];
        if (c == ' ' || c == '\n' || c == '\t') {
            if (word != "") {
                if (word == word_to_replace)
                    newStatus += new_word;
                else
                    newStatus += word;
                word = "";
            }
            newStatus += c;
        }
        else {
            word += c;
        }
    }

    if (word != "") {
        if (word == word_to_replace)
            newStatus += new_word;
        else
            newStatus += word;
    }

    this->page.setStatus(newStatus);

}