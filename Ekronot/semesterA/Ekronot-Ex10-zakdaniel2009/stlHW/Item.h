#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

enum ItemCategory { NONE = 0, FOOD = 1, PHARM = 2, CLEANING = 3, HOME = 4 };

std::string getItemCategoryString(ItemCategory type);

class Item
{
public:
    Item(const std::string& name, const std::string& serial, double Price, ItemCategory category);

    double totalPrice() const;

    bool operator<(const Item& other) const;
    bool operator>(const Item& other) const;
    bool operator==(const Item& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Item& item);

    std::string getSerial() const;
    std::string getName() const;
    ItemCategory getCategory() const;
    double getPrice() const;
    int getCount() const;

    void setName(const std::string& name);
    void setCategory(ItemCategory category);
    void setPrice(double price);
    void setCount(int count);

private:
    std::string _serial;
    std::string _name;
    ItemCategory _category;
    double _Price;
    int _count;
};
