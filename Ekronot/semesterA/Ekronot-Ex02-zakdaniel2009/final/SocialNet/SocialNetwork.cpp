#include "SocialNetwork.h"

void SocialNetwork::init(const std::string& networkName, int minAge) {
	this->name = networkName;
	this->minAge = minAge;
	this->profiles.init();
}

void SocialNetwork::clear() {
	this->profiles.clear();
	this->name.clear();
	this->minAge = 0;
}

std::string SocialNetwork::getNetworkName() const {
	return this->name;
}

int SocialNetwork::getMinAge() const {
	return this->minAge;
}

bool SocialNetwork::addProfile(Profile profile_to_add) {
	if (profile_to_add.getOwner().getAge() < this->minAge)
		return false;
	bool ans = this->profiles.add(profile_to_add);
	return ans;
}
std::string SocialNetwork::getWindowsDevices() {
	std::string result = "";
	ProfileNode* current = this->profiles.get_first();

	while (current != nullptr) {
		DevicesList& devices = current->get_data().getOwner().getDevices();
		DeviceNode* deviceCurrent = devices.get_first();

		while (deviceCurrent != nullptr) {
			std::string os = deviceCurrent->get_data().getOS();
			if (os == WINDOWS7 || os == WINDOWS10 || os == WINDOWS11) {
				if (!result.empty()) {
					result += ", ";
				}

				result += std::string("[") + std::to_string(deviceCurrent->get_data().getID()) + ", " + os + "]";
			}

			deviceCurrent = deviceCurrent->get_next();
		}
		current = current->get_next();
	}
	return result;
}