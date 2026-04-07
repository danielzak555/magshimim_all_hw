#include "Customer.h"

Customer::Customer(std::string name) 
	: _name(name)
{
}
Customer::Customer() 
	: _name("")
{
}

Customer::~Customer() {
	for (auto& pair : _shoppingCarts) {
		delete pair.second;
	}
}

void Customer::createNewShoppingCart(const std::string& shoppingCartName) {
	_shoppingCarts[shoppingCartName] = new std::set<Item>();
}
double Customer::shoppingCartSum(const std::string& shoppingCartName) const {
	double sum = 0.0;
	auto it = _shoppingCarts.find(shoppingCartName);
	if (it != _shoppingCarts.end()) {
		for (const auto& item : *(it->second)) {
			sum += item.totalPrice();
		}
	}

	return sum;
}
double Customer::totalSum() const {
	double total = 0.0;
	for (const auto& pair : _shoppingCarts) {
		for (const auto& item : *(pair.second)) {
			total += item.totalPrice();
		}
	}
	return total;
}

void Customer::addItem(const Item& item, const std::string& shoppingCartName) {
	if (_shoppingCarts.find(shoppingCartName) != _shoppingCarts.end()) {
		if (!_shoppingCarts.at(shoppingCartName)->insert(item).second) {
			auto it = _shoppingCarts.at(shoppingCartName)->find(item);
			if (it != _shoppingCarts.at(shoppingCartName)->end()) {
				Item updatedItem = *it;
				_shoppingCarts.at(shoppingCartName)->erase(it);
				updatedItem.setCount(updatedItem.getCount() + 1);
				_shoppingCarts.at(shoppingCartName)->insert(updatedItem);
			}
		}
	}
}
void Customer::removeItem(const Item& item, const std::string& shoppingCartName) {
	if(_shoppingCarts.find(shoppingCartName) != _shoppingCarts.end()) {
		auto it = _shoppingCarts.at(shoppingCartName)->find(item);
		if (it != _shoppingCarts.at(shoppingCartName)->end()) {
			Item updatedItem = *it;
			_shoppingCarts.at(shoppingCartName)->erase(it);
			if (updatedItem.getCount() > 1) {
				updatedItem.setCount(updatedItem.getCount() - 1);
				_shoppingCarts.at(shoppingCartName)->insert(updatedItem);
			}
		}
	}
}

std::string Customer::getName() const {
	return _name;
}
std::set<Item>* Customer::getShoppingCart(std::string shoppingCartName) const {
	return _shoppingCarts.at(shoppingCartName);
}

std::vector<std::string> Customer::getCartNames() const {
	std::vector<std::string> names;
	for (auto const& pair : _shoppingCarts) {
		names.push_back(pair.first);
	}
	return names;
}

std::map<std::string, std::set<Item>*> Customer::getAllCarts() const {
	return this->_shoppingCarts;
}