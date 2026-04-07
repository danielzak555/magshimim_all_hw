#pragma once
#include"Item.h"
#include<set>
#include<map>
#include<vector>

class Customer
{
public:
	Customer(std::string name);
	Customer();

	~Customer();
	
	void createNewShoppingCart(const std::string& shoppingCartName);
	double shoppingCartSum(const std::string& shoppingCartName) const;
	double totalSum() const;

	void addItem(const Item& item, const std::string& shoppingCartName);
	void removeItem(const Item& item, const std::string& shoppingCartName);

	std::string getName() const;
	std::set<Item>* getShoppingCart(std::string shoppingCartName) const;
	std::vector<std::string> getCartNames() const;
	std::map<std::string, std::set<Item>*> getAllCarts() const;

private:
	std::string _name;
	std::map<std::string , std::set<Item>*> _shoppingCarts;


};
