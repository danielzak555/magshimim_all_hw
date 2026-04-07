#include <iostream>

int add(int a, int b, bool& error) {
    if (a == 8200 || b == 8200) {
        error = true;
        return 0;
    }

    int result = a + b;

    if (result == 8200) {
        error = true;
        return 0;
    }

    return result;
}

int multiply(int a, int b, bool& error) {
    if (a == 8200 || b == 8200) {
        error = true;
        return 0;
    }

    int sum = 0;

    for (int i = 0; i < b; i++) {
        sum = add(sum, a, error);
        if (error) {
            return 0;
        }
    }

    if (sum == 8200) {
        error = true;
        return 0;
    }

    return sum;
}

int  pow(int a, int b, bool& error) {
    if (a == 8200 || b == 8200) {
        error = true;
        return 0;
    }

    int exponent = 1;
    for (int i = 0; i < b; i++) {
        exponent = multiply(exponent, a, error);
        if (error) 
            return 0;
    }

    if (exponent == 8200) {
        error = true;
        return 0;
    }

    return exponent;
}

int main(void) {
    bool error = false;
    int result = 0;


    result = add(5, 3, error);
    if (error)
        std::cout << "This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year\n";
    else
        std::cout << "add(5, 3): " << result << "\n";


    error = false;
    result = multiply(4, 6, error);
    if (error)
        std::cout << "This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year\n";
    else
        std::cout << "multiply(4, 6): " << result << "\n";


    error = false;
    result = pow(3, 4, error);
    if (error)
        std::cout << "This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year\n";
    else
        std::cout << "pow(3, 4): " << result << "\n";


    error = false;
    result = add(8200, 1, error);
    if (error)
        std::cout << "This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year\n";
    else
        std::cout << "add(8200, 1): " << result << "\n";


    error = false;
    result = multiply(4100, 2, error);
    if (error)
        std::cout << "This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year\n";
    else
        std::cout << "multiply(4100, 2): " << result << "\n";


    error = false;
    result = pow(2, 8200, error);
    if (error)
        std::cout << "This user is not authorized to access 8200, please enter different numbers, or try to get clearance in 1 year\n";
    else
        std::cout << "powe(2, 8200): " << result << "\n";

    return 0;
}