#pragma once

#include <string>
#include "ProfileList.h"

class SocialNetwork
{
private:

    unsigned int minAge;
    std::string name;
    ProfileList profiles;

public:
    void init(const std::string& networkName, int minAge);
    void clear();
    std::string getNetworkName() const;
    int getMinAge() const;
    bool addProfile(Profile profile_to_add);
    std::string getWindowsDevices();
};
