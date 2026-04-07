#pragma once

#include <algorithm>
#include <iostream>

template <typename T>
int compare(const T& a, const T& b)
{
    if (a > b)
        return -1;
    if (a == b)
        return 0;
    return 1;
}

template <typename T>
void bubbleSort(T arr[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(arr[j], arr[j + 1]) == -1) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

template <typename T>
void printArray(const T arr[], int n)
{
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << std::endl;
	}
}