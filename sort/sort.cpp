//
// Created by spendar on 2022/3/14.
//
#include "sort.h"


void Sort::bubbleSort(std::vector<int>& arr) {
	int size = arr.size();
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size-i-1; j++) {
			if(arr[j] > arr[j+1]) {
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

void Sort::selectSort(std::vector<int>& arr) {
	int size = arr.size();
	for(int i = 0; i < size; i++) {
		int index = 0;
		int temp = arr[0];
		for(int i = 0; i < size-i; i++) {
			if(arr[i] > temp) {
				index = i;
				temp = arr[i];
			}
		}
		arr[size-1-i] = arr[index]; 
		arr[index] = temp;
	}
}

void Sort::insertSort(std::vector<int>& arr) {
	int size = arr.size();
	for(int i = 1; i < size; i++) {
		int temp = arr[i];
		int index = i;
		while(index > 0 && arr[index-1] < temp) {
			arr[index] = arr[index-1];
		}
		arr[index] = temp;
	}
}

void Sort::shellSort(std::vector<int>& arr) {
	int size = arr.size();
	for(int gap = size/2; gap > 0; gap /= 2){
		for(int i = gap; i < size; i++){
			int index = i-gap;
			int temp = arr[i];
			while(index > 0 && temp < arr[index]) {
				arr[index+gap] = arr[index];
				index -= gap;
			}
			arr[index+gap] = temp;
		}
	}
}

void merge(std::vector<int>& arr, int left, int right) {
	if(left >= right) {
		return;
	}
	int mid = (right - left) / 2 + left;
	merge(arr, left, mid);
	merge(arr, mid+1, right);
	int temp[right-left+1];
	int index = 0;
	int l = left;
	int r = mid + 1;
	while(l <= mid && r <= right) {
		if(arr[l] <= arr[r]) {
			temp[index++] = arr[l++];
		} else {
			temp[index++] = arr[r++];
		}
	}
	while(l <= mid) {
		temp[index++] = arr[l++];
	}
	while(r <= right) {
		temp[index++] = arr[r++];
	}
	for(int i = left; i <= right; i++) {
		arr[i] = temp[i-left];
	}
}

void Sort::mergeSort(std::vector<int>& arr) {
	merge(arr, 0, arr.size()-1);
}

void Sort::heapSort(std::vector<int>& arr) {
	std::priority_queue<int> pq;
	for(int a : arr) {
		pq.push(a);
	}
	int size = arr.size();
	for(int i = size-1; i >= 0; i--) {
		arr[i] = pq.top();
		pq.pop();
	}
}

void quick(std::vector<int>& arr, int left, int right) {
	if(left >= right) {
		return;
	}
	int key = arr[left];
	int l = left;
	int r = right;
	while(l < r) {
		while(l < r && arr[r] >= key) {
			r--;
		}
		if(l < r) {
			arr[l] = arr[r];
		}
		while(l < r && arr[l] <= key) {
			l++;
		}
		if(l < r) {
			 arr[r] = arr[l];
		}
	}
	arr[l] = key;
	quick(arr, left, l-1);
	quick(arr, l+1, right);
}

void Sort::quickSort(std::vector<int>& arr) {
	quick(arr, 0, arr.size()-1);
}

void Sort::countSort(std::vector<int>& arr) {
	int maxn = 0x80000000;
	int minn = 0x7fffffff;
	for(int a : arr) {
		maxn = std::max(maxn, a);
		minn = std::min(minn, a);
	}
	int data[maxn - minn+1];
	int index = 0;
	for(int i = 0; i < maxn - minn+1; i++) {
		data[i] = 0;
	}
	for(int a : arr) {
		data[a-minn]++;
	}
	for(int i = 0; i < maxn - minn+1; i++) {
		for(int j = 0; j < data[i]; j++) {
			arr[index++] = i + minn;
		}
	}
}

void Sort::bucketSort(std::vector<int>& arr) {
	int nums_max = arr[0];
	int nums_min = arr[0];
	for(int i = 0; i < arr.size(); i++){
		if(arr[i] < nums_min)
			nums_min = arr[i];
		if(arr[i] > nums_max)
			nums_max = arr[i];
	}
	int gap = (nums_max - nums_min) / 5 + 1;
	std::vector<int> buckets[5];
	for(int i = 0; i < arr.size(); i++)
		buckets[(arr[i] - nums_min) / gap].push_back(arr[i]);
	for(int i = 0; i < 5; i++){
		quick(buckets[i], 0, buckets[i].size()-1);
	}
	int index = 0;
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < buckets[i].size(); j++) {
			arr[index++] = buckets[i][j];
		}
	}
}

void Sort::radixSort(std::vector<int>& arr) {
	int size = arr.size();
	int nums_max = arr[0];
	for(int i = 0; i < size; i++)
		if(nums_max < arr[i])
			nums_max = arr[i];
	int radix = 1;
	while(nums_max /= 10)
		radix++;
	for(int k = 0; k < radix; k++){
		std::vector<int> radixes[10];
		for(int i = 0; i < size; i++)
			radixes[arr[i]/((int)(pow(10, k))%10)].push_back(arr[i]);
		int index = 0;
		for(int i = 0; i < 10; i++)
			for(int j = 0; j < radixes[i].size(); j++)
				arr[index++] = radixes[i][j];
		}
}