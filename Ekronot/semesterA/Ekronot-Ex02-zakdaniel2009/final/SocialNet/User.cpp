#include "User.h"

void User::init(unsigned int id, const std::string& username, unsigned int age) {
    this->id = id;
    this->username = username;
    this->age = age;
    this->devices.init();
}

void User::addDevice(Device newDevice) {
    this->devices.add(newDevice);
}

DevicesList& User::getDevices() {
    return this->devices;
}

unsigned int User::getAge() const {
    return this->age;
}

std::string User::getUserName() const {
    return this->username;
}

unsigned int User::getID() const {
    return this->id;
}

bool User::checkIfDevicesAreOn() const {
    DeviceNode* curr = this->devices.get_first();
    while (curr != nullptr) {
        if (curr->get_data().isActive() == false)
            return false;
        curr = curr->get_next();
    }
    return true;
}

void User::clear() {
    this->devices.clear();
}
