#pragma once

#include <iostream>
#include <algorithm>

template <typename T>
class BSNode
{
public:
    BSNode(const T& data);
    BSNode(const BSNode<T>& other);
    ~BSNode();
    void insert(const T& value);
    BSNode<T>& operator=(const BSNode<T>& other);
    bool isLeaf() const;
    T getData() const;
    int getCount() const;
    BSNode<T>* getLeft() const;
    BSNode<T>* getRight() const;
    bool search(const T& val) const;
    int getHeight() const;
    int getDepth(const BSNode<T>& root) const;
    void printNodes() const;

private:
    T _data;
    BSNode<T>* _left;
    BSNode<T>* _right;
    int _count;

    int getCurrNodeDistFromInputNode(const BSNode<T>* node) const;
};

template <typename T>
BSNode<T>::BSNode(const T& data)
    : _data(data), _left(nullptr), _right(nullptr), _count(1)
{
}

template <typename T>
BSNode<T>::BSNode(const BSNode<T>& other)
    : _data(other._data), _left(nullptr), _right(nullptr), _count(other._count)
{
    if (other._left)
        _left = new BSNode<T>(*other._left);
    if (other._right)
        _right = new BSNode<T>(*other._right);
}

template <typename T>
BSNode<T>::~BSNode()
{
    delete _left;
    delete _right;
}

template <typename T>
void BSNode<T>::insert(const T& value)
{
    if (value == _data)
        _count++;
    else if (value < _data)
    {
        if (_left)
            _left->insert(value);
        else
            _left = new BSNode<T>(value);
    }
    else
    {
        if (_right)
            _right->insert(value);
        else
            _right = new BSNode<T>(value);
    }
}

template <typename T>
BSNode<T>& BSNode<T>::operator=(const BSNode<T>& other)
{
    if (this == &other)
        return *this;

    delete _left;
    delete _right;

    _data = other._data;
    _count = other._count;
    _left = other._left ? new BSNode<T>(*other._left) : nullptr;
    _right = other._right ? new BSNode<T>(*other._right) : nullptr;

    return *this;
}

template <typename T>
bool BSNode<T>::isLeaf() const
{
    return !_left && !_right;
}

template <typename T>
T BSNode<T>::getData() const
{
    return _data;
}

template <typename T>
int BSNode<T>::getCount() const
{
    return _count;
}

template <typename T>
BSNode<T>* BSNode<T>::getLeft() const
{
    return _left;
}

template <typename T>
BSNode<T>* BSNode<T>::getRight() const
{
    return _right;
}

template <typename T>
bool BSNode<T>::search(const T& val) const
{
    if (val == _data)
        return true;
    if (val < _data)
        return _left ? _left->search(val) : false;
    return _right ? _right->search(val) : false;
}

template <typename T>
int BSNode<T>::getHeight() const
{
    int lh = _left ? _left->getHeight() : -1;
    int rh = _right ? _right->getHeight() : -1;
    return 1 + std::max(lh, rh);
}

template <typename T>
int BSNode<T>::getDepth(const BSNode<T>& root) const
{
    if (this == &root)
        return 0;
    return getCurrNodeDistFromInputNode(&root);
}

template <typename T>
void BSNode<T>::printNodes() const
{
    if (_left)
        _left->printNodes();

    std::cout << _data << " " << _count << std::endl;

    if (_right)
        _right->printNodes();
}

template <typename T>
int BSNode<T>::getCurrNodeDistFromInputNode(const BSNode<T>* node) const
{
    if (!node)
        return -1;
    if (this == node)
        return 0;

    int d = getCurrNodeDistFromInputNode(node->getLeft());
    if (d >= 0)
        return d + 1;

    d = getCurrNodeDistFromInputNode(node->getRight());
    if (d >= 0)
        return d + 1;

    return -1;
}
