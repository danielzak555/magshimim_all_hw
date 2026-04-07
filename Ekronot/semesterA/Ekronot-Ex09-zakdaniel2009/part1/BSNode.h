#pragma once

#include <string>
#include <iostream>
#include <algorithm>

class BSNode
{
public:
    BSNode(const std::string& data);
    BSNode(const BSNode& other);
    ~BSNode();
    void insert(const std::string& value);
    BSNode& operator=(const BSNode& other);
    bool isLeaf() const;
    std::string getData() const;
    int getCount() const;
    BSNode* getLeft() const;
    BSNode* getRight() const;
    bool search(const std::string& val) const;
    int getHeight() const;
    int getDepth(const BSNode& root) const;
    void printNodes() const;

private:
	std::string _data;
	BSNode* _left;
	BSNode* _right;
	int _count;
	int getCurrNodeDistFromInputNode(const BSNode* node) const;

};