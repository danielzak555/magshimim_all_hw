#include <iostream>
#include <stdexcept>

int add(int a, int b) {
    if (a == 8200 || b == 8200)
        throw std::runtime_error("This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year");

    if (a + b == 8200)
        throw std::runtime_error("This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year");
    return a + b;
}

int  multiply(int a, int b) {
  int sum = 0;

  if (a == 8200 || b == 8200)
      throw std::runtime_error("This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year");

  for(int i = 0; i < b; i++) {
    sum = add(sum, a);
    if (sum == 8200)
        throw std::runtime_error("This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year");
  }
  return sum;
}

int  pow(int a, int b) {
  int exponent = 1;

  if (a == 8200 || b == 8200)
      throw std::runtime_error("This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year");

  for(int i = 0; i < b; i++) {
    exponent = multiply(exponent, a);
    if (exponent == 8200)
        throw std::runtime_error("This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year");
  }
  return exponent;
}

int main(void) {
    try {
        std::cout << "add(5, 3): " << add(5, 3) << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    try {
        std::cout << "multiply(4, 6): " << multiply(4, 6) << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    try {
        std::cout << "pow(3, 4): " << pow(3, 4) << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    try {
        std::cout << "add(8200, 1): " << add(8200, 1) << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    try {
        std::cout << "multiply(4100, 2): " << multiply(4100, 2) << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    try {
        std::cout << "pow(2, 8200): " << pow(2, 8200) << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}