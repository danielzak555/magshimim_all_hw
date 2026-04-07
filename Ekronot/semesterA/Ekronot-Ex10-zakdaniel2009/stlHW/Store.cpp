#include "Store.h"
#include <fstream>
#include <sstream>

void Store::getInventoryFromFile(const std::string inventoryFileName)
{
	// This function reads a CSV file into the object inventory (std::deque<Item>)

	std::deque<std::deque<std::string>> content;	// the entire file as strings
	std::deque<std::string> row;					// a row in the file as string
	std::string line, word;							

	std::fstream file(inventoryFileName, std::ios::in);		// openning the csv file for read
	if (file.is_open())
	{
		while (std::getline(file, line))		// reading line by line
		{
			row.clear();

			std::stringstream str(line);		// adding the line to a std::stringstream

			while (std::getline(str, word, ','))	// reading each word seperated by ','
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
	{
		std::cerr << "Could not open the file " << inventoryFileName << "\n" << std::endl;
		throw std::invalid_argument("Could not open the file " + inventoryFileName);
	}

	/* Indexes
		0 --- Item's Name
		1 --- Item's Serial
		2 --- Item's Unit Price
		3 --- Item's Category (int)
	*/

	for (int i = 1; i < content.size(); i++)
	{
		std::string itemName = content[i][0];
		std::string itemSerial = content[i][1];
		double itemPrice = strtod(content[i][2].c_str(), nullptr);
		ItemCategory itemCategory = ItemCategory(stoi(content[i][3]));
		this->_products.push_back(Item(itemName, itemSerial, itemPrice, itemCategory));
	}

	// To print the content remove the comments:
	// for (int i = 0; i < content.size(); i++)
	//{
	//	for (int j = 0; j < content[i].size(); j++)
	//	{
	//		std::cout << content[i][j] << " ";
	//	}
	//	std::cout << "\n";
	//}

}



Store::Store(const std::string& storeName, const std::string& inventoryFileName) 
	: _storeName(storeName)
{
	getInventoryFromFile(inventoryFileName);
}
std::string Store::getName() const {
	return _storeName;
}
std::deque<Item> Store::getProducts() const {
	return _products;
}
void Store::setName(const std::string& storeName) {
	_storeName = storeName;
}
void Store::setProducts(const std::deque<Item>& products) {
	_products = products;
}
std::string Store::getSortedProductList(SortingCriteria criteria) const {
	std::string final = "";
	std::deque<Item> sortedProducts = _products;
	std::sort(sortedProducts.begin(), sortedProducts.end(), [criteria](const Item& a, const Item& b) {
			switch (criteria) {
			case CATEGORY:
				return a.getCategory() < b.getCategory();
			case NAME:
				return a.getName() < b.getName();
			case PRICE:
				return a.getPrice() < b.getPrice();
			case SERIAL:
				return a.getSerial() < b.getSerial();
			default:
				return false;
			}
	});
	for (const auto& item : sortedProducts) {
		final += "[Serial: " + item.getSerial() +
			", Name: " + item.getName() +
			", Category: " + getItemCategoryString(item.getCategory()) +
			", Price: " + std::to_string(item.getPrice()) +
			", Amount: " + std::to_string(item.getCount()) +
			"]\n";
	}

	return final;
}
std::string Store::getProductListFilteredByCategory(ItemCategory category) const {
	std::string final = "";
	std::deque<Item> filteredProducts;
	for(const auto& item : _products) {
		if(item.getCategory() == category) {
			filteredProducts.push_back(item);
		}
	}

	std::sort(filteredProducts.begin(), filteredProducts.end(), [](const Item& a, const Item& b) {
		return a.getName() < b.getName();
		});
	for (const auto& item : filteredProducts) {
		final += "[Serial: " + item.getSerial() +
			", Name: " + item.getName() +
			", Category: " + getItemCategoryString(item.getCategory()) +
			", Price: " + std::to_string(item.getPrice()) +
			", Amount: " + std::to_string(item.getCount()) +
			"]\n";
	}

	return final;
}

Item Store::operator[](const int itemNumber) const {
	if (itemNumber < 0 || itemNumber >= _products.size()) {
		throw std::invalid_argument("Item number out of range");
	}
	return _products[itemNumber];
}

std::ostream& operator<<(std::ostream& os, const Store& store)
{
	os << "Store Name: " << store._storeName << "\nProducts:\n";
	int i = 0;
	for (const auto& item : store._products) {
		os << "[" << i++ << "] - " << item << "\n";
	}
	return os;
}