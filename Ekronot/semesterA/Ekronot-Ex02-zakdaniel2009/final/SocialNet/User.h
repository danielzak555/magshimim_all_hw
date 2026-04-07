#pragma once
#include <string>
#include "DeviceList.h"

class User
{
private:
    unsigned int id;
	std::string username;
	unsigned int age;
	DevicesList devices;

public:

    void init(unsigned int id, const std::string& username, unsigned int age);

    void addDevice(Device newDevice);
    DevicesList& getDevices() ;// the const made me problems :(
    unsigned int getAge() const;
    std::string getUserName() const;
    unsigned int getID() const;

    bool checkIfDevicesAreOn() const;
    void clear();
};