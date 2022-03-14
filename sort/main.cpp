#include <iostream>
#include <vector>
#include "sort.h"

using namespace std;

void printArray(vector<int> &arr) {
    for(auto a : arr) {
        cout<<a<<" ";
    }
    cout<<endl;
}

int main() {
    vector<int> arr = {8,4,9,1,2,0,3,7,5,6,3,7};
    Sort* sort = new Sort();
    sort->radixSort(arr);
    printArray(arr);
    return 0;
}