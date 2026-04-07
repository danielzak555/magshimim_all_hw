#include "BSNode.h"

BSNode::BSNode(const std::string& data)
	:_data(data), _left(nullptr), _right(nullptr), _count(1)
{
}
BSNode::BSNode(const BSNode& other) 
	: _data(other._data), _left(nullptr), _right(nullptr), _count(other._count)
{
    if (other._left)
        _left = new BSNode(*other._left);

    if (other._right)
        _right = new BSNode(*other._right);
}
BSNode::~BSNode() {
    delete _left;
    delete _right;
}

void BSNode::insert(const std::string& value) {
    if(value == _data) {
        _count++;
    }
    else if(value < _data) {
        if(_left == nullptr) {
            _left = new BSNode(value);
        } 
        else {
            _left->insert(value);
        }
    } 
    else {
        if(_right == nullptr) {
            _right = new BSNode(value);
        } 
        else {
            _right->insert(value);
        }
	}
}

BSNode& BSNode::operator=(const BSNode& other) {
	this->_data = other._data;
    this->_count = other._count;
    delete this->_left;
    delete this->_right;
    this->_left = other._left ? new BSNode(*other._left) : nullptr;
	this->_right = other._right ? new BSNode(*other._right) : nullptr;

    return *this;
}

bool BSNode::isLeaf() const {
    if (_left == nullptr && _right == nullptr) {
        return true;
	}
    return false;
}
std::string BSNode::getData() const {
    return _data;
}
int BSNode::getCount() const {
    return _count;
}

BSNode* BSNode::getLeft() const {
    return _left;
}
BSNode* BSNode::getRight() const {
    return _right;
}

bool BSNode::search(const std::string& val) const {
    if (val == _data) {
        return true;
    } 
    else if (val < _data) {
        if (_left != nullptr) {
            return _left->search(val);
        } 
        else {
            return false;
        }
    } 
    else {
        if (_right != nullptr) {
            return _right->search(val);
        } 
        else {
            return false;
        }
	}   
}

int BSNode::getHeight() const {
	int leftHeight = (_left != nullptr) ? _left->getHeight() : -1;
	int rightHeight = (_right != nullptr) ? _right->getHeight() : -1;
	return 1 + std::max(leftHeight, rightHeight);
}
int BSNode::getDepth(const BSNode& root) const {
    if (this == &root) {
        return 0;
	}
	return getCurrNodeDistFromInputNode(&root);
}

void BSNode::printNodes() const {
    if (_left != nullptr)
        _left->printNodes();

    std::cout << _data << " " << _count << std::endl;

    if (_right != nullptr)
        _right->printNodes();
}

int BSNode::getCurrNodeDistFromInputNode(const BSNode* node) const {
    if (node == nullptr)
        return -1;

    if (this == node)
        return 0;

    int distance = -1;

    distance = getCurrNodeDistFromInputNode(node->getLeft());
    if (distance >= 0)
        return distance + 1;

    distance = getCurrNodeDistFromInputNode(node->getRight());
    if (distance >= 0)
        return distance + 1;

    return -1;
}