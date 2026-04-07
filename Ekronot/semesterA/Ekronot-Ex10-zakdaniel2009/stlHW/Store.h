#pragma once
#include <string>
#include <iostream>
#include <deque>
#include "Item.h"
#include <algorithm>

// More examples here:
// https://www.geeksforgeeks.org/comparator-class-in-c-with-examples/

struct {
	bool operator()(const Item& a, const Item& b)
	{
		return a.getCategory() < b.getCategory();
	}
} CategoryComparator;

struct {
	bool operator()(const Item& a, const Item& b)
	{
		return 	a.getName() < b.getName();
	}
} NameComparator;

struct {
	bool operator()(const Item& a, const Item& b)
	{
		return a.getPrice() < b.getPrice();
	}
} PriceComparator;


enum SortingCriteria {CATEGORY = 0, NAME = 1, PRICE = 2, SERIAL = 3};

class Store
{
public:

	Store(const std::string& storeName, const std::string& inventoryFileName);

	std::string getName() const;
	std::deque<Item> getProducts() const;
	void setName(const std::string& storeName);
	void setProducts(const std::deque<Item>& products);
	
	std::string getSortedProductList(SortingCriteria criteria) const;
	std::string getProductListFilteredByCategory(ItemCategory category) const;

	Item operator[](const int itemNumber) const;

	friend std::ostream& operator<<(std::ostream& os, const Store& store);

private:

    // Helper Method, reads a '.csv' file and adding the items to the products list.
	void getInventoryFromFile(const std::string inventoryFileName);

    ////////////
    // Fields //
    ////////////

	std::string _storeName;
	std::deque<Item> _products;
};
 
