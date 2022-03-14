//
// Created by spendar on 2022/3/14.
//

#ifndef INC_1_SORT_H
#define INC_1_SORT_H

#include <vector>
#include <queue>
#include <cmath>


class Sort {
public:
    Sort() {};

    void bubbleSort(std::vector<int>& arr);

    void selectSort(std::vector<int>& arr);

    void insertSort(std::vector<int>& arr);

    void shellSort(std::vector<int>& arr);

    void mergeSort(std::vector<int> &arr);

    void quickSort(std::vector<int>& arr);

    void heapSort(std::vector<int>& arr);

    void countSort(std::vector<int>& arr);

    void bucketSort(std::vector<int>& arr);

    void radixSort(std::vector<int>& arr);

};


#endif //INC_1_SORT_H
