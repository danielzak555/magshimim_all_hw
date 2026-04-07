#include "Item.h"

std::string getItemCategoryString(ItemCategory type)
{
    if (type == NONE) return "NONE";
    if (type == FOOD) return "Food";
    if (type == PHARM) return "Pharm";
    if (type == CLEANING) return "Cleaning";
    if (type == HOME) return "Home";
    return "Unknown";
}

Item::Item(const std::string& name, const std::string& serial, double Price, ItemCategory category)
    :_name(name),
    _category(category),
	_count(1)
{
    if (serial.length() != 5 || Price < 0)
        throw std::invalid_argument("serial not 5 or neg price");
    else {
        _serial = serial;
        _Price = Price;
    }
}

double Item::totalPrice() const
{
    return _Price * _count;
}

bool Item::operator<(const Item& other) const
{
    return _serial < other._serial;
}

bool Item::operator>(const Item& other) const
{
    return _serial > other._serial;
}

bool Item::operator==(const Item& other) const
{
    return _serial == other._serial;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    os << "Item[Serial=" << item._serial
       << ", Name=" << item._name
       << ", Category=" << getItemCategoryString(item._category)
       << ", UnitPrice=" << item._Price
       << ", Count=" << item._count
       << ", Total=" << item.totalPrice()
       << "]";
    return os;
}

std::string Item::getSerial() const 
{
    return _serial; 
}
std::string Item::getName() const 
{
    return _name; 
}
ItemCategory Item::getCategory() const 
{
    return _category; 
}
double Item::getPrice() const 
{
    return _Price; 
}
int Item::getCount() const 
{
    return _count; 
}
void Item::setName(const std::string& name) 
{
    _name = name; 
}
void Item::setCategory(ItemCategory category) 
{
    _category = category; 
}
void Item::setPrice(double price) 
{   
    if (price < 0)
        throw std::invalid_argument("count price cannot be negative");
    _Price = price; 
}
void Item::setCount(int count) 
{   
    if (count < 0) 
		throw std::invalid_argument("Count cannot be negative.");
    _count = count; 
}
