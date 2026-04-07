#include "Vector.h"

Vector::Vector(int n){
    if (n < 2) {
        _capacity = 2;
        _resizeFactor = 2;
    }
    else {
        _capacity = n;
        _resizeFactor = n;
    }

    _size = 0;
    _elements = new int[_capacity];

    for (int i = 0; i < _capacity; i++) {
        _elements[i] = 0;
    }
}

Vector::~Vector(){
    delete[] _elements;
    _elements = nullptr;
    _size = 0;
    _resizeFactor = 0;
    _capacity = 0;
}

int Vector::size() const{
    return _size;

}

int Vector::capacity() const{
    return _capacity;
}

int Vector::resizeFactor() const{
	return _resizeFactor;
}
bool Vector::empty() const{
    return _size == 0;
}


void Vector::push_back(const int& val){
    if (_size >= _capacity) {
        reserve(_capacity + _resizeFactor);
        _elements[_size] = val;
	    _size++;
	}
    
    else{
        _elements[_size] = val;
        _size++;
	}
}

int Vector::pop_back(){
    if (_size == 0) {
		std::cout << "error: pop from empty vector" << std::endl;
        return -9999;
	}
    else {
        _size--;
		return _elements[_size];
    }
}

void Vector::reserve(const int n){
	int newCapacity = _capacity;
    if (n > _capacity) {
        while (newCapacity < n) {
            newCapacity += _resizeFactor;
        }
        int* newElements = new int[newCapacity];
        for (int i = 0; i < _size; i++) {
            newElements[i] = _elements[i];
        }
        delete[] _elements;
        _elements = newElements;
        _capacity = newCapacity;
	}
}

void Vector::resize(const int n) {
    if (n < _size) {
        _size = n;
        return;
    }
    if (n > _capacity) {
        reserve(n);
    }
    for (int i = _size; i < n; i++) {
        _elements[i] = 0;
    }
    _size = n;
}

void Vector::assign(const int val){
    for(int i = 0; i < _size; i++) {
        _elements[i] = val;
	}
}

void Vector::resize(const int n, const int& val){
    if (n < _size) {
        _size = n;
        return;
    }
    if (n > _capacity) {
        reserve(n);
    }
    for (int i = _size; i < n; i++) {
        _elements[i] = val;
    }
    _size = n;
}

Vector::Vector(const Vector& other){
	_capacity = other._capacity;
	_size = other._size;
	_resizeFactor = other._resizeFactor;
	_elements = new int[_capacity];
    for (int i = 0; i < _size; i++) {
        _elements[i] = other._elements[i];
	}
    for (int i = _size; i < _capacity; i++) {
        _elements[i] = 0;
    }
}
Vector& Vector::operator=(const Vector& other){
    delete[] _elements;
	_capacity = other._capacity;
	_size = other._size;
	_resizeFactor = other._resizeFactor;
    _elements = new int[_capacity];
    for (int i = 0; i < _size; i++) {
        _elements[i] = other._elements[i];
    }
    for (int i = _size; i < _capacity; i++) {
        _elements[i] = 0;
    }
	return *this;
}

int& Vector::operator[](int n) const{
    if(n < 0 || n >= _size) {
        std::cerr << "error: index out of the bounds" << std::endl;
        return _elements[0];
	}
	return _elements[n];
}//n'th element

Vector& Vector::operator+=(const Vector& other){
    int newSize = (_size > other._size) ? _size : other._size;
    if (newSize > _capacity) {
        reserve(newSize);
    }
    for (int i = 0; i < newSize; i++) {
        int val1 = (i < _size) ? _elements[i] : 0;
        int val2 = (i < other._size) ? other._elements[i] : 0;
        _elements[i] = val1 + val2;
    }

    _size = newSize;

    return *this;
}
Vector& Vector::operator-=(const Vector& other){
    int newSize = (_size > other._size) ? _size : other._size;
    if (newSize > _capacity) {
        reserve(newSize);
    }
    for (int i = 0; i < newSize; i++) {
        int val1 = (i < _size) ? _elements[i] : 0;
        int val2 = (i < other._size) ? other._elements[i] : 0;
        _elements[i] = val1 - val2;
    }
    _size = newSize;

    return *this;
}
Vector Vector::operator+(const Vector& other) const{
    int newSize = (_size > other._size) ? _size : other._size;
    Vector result(newSize);
    result._size = newSize;
    for (int i = 0; i < newSize; i++) {
        int val1 = (i < _size) ? _elements[i] : 0;
        int val2 = (i < other._size) ? other._elements[i] : 0;
        result._elements[i] = val1 + val2;
    }

    return result;
}
Vector Vector::operator-(const Vector& other) const{
    int newSize = (_size > other._size) ? _size : other._size;
    Vector result(newSize);
    result._size = newSize;
    for (int i = 0; i < newSize; i++) {
        int val1 = (i < _size) ? _elements[i] : 0;
        int val2 = (i < other._size) ? other._elements[i] : 0;
        result._elements[i] = val1 - val2;
    }

    return result;
}
std::ostream& operator<<(std::ostream& os, const Vector& v){
    os << "Vector info:" << std::endl;
    os << "Capacity is " << v.capacity() << std::endl;
	os << "Size is " << v.size() << std::endl;
    os << "{";
    for (int i = 0; i < v.size(); i++) {
        os << v[i];
        if (i != v.size() - 1) {
            os << ",";
        }
    }
	os << "}\n";
	return os;
}