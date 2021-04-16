#include <vector>

class Sort{

	//冒泡排序 时间复杂度 O(n^2) 空间复杂度 O(1)
	void bubbleSort(vector<int> &nums){
		int size = nums.size();
		for(int i = 0; i < size; i++)
			for(int j = 0; j < size-i-1; j++)
				if(nums[j] > nums[j+1]){
					int temp = nums[j];
					nums[j] = nums[j+1];
					nums[j+1] = temp;
				}
	}

	//选择排序 时间复杂度 O(n^2) 空间复杂度 O(1)
	void selectSort(vector<int> &nums){
		int size = nums.size();
		for(int i = 0; i < size; i++){
			int m = nums[0];
			int index = 0;
			for(int j = 0; j < size-i; j++){
				if(m < nums[j]){
					m = nums[i];
					index = j;
				}
			}
			int temp = nums[size-i-1];
			nums[size-i-1] = m;
			nums[index] = temp;
		}
	}

	//插入排序 时间复杂度 O(n^2) 空间复杂度 O(1)
	void insertSort(vector<int> &nums){
	    int size = nums.size();
	    for(int i = 0; i < size; i++){
	        int index = i-1;
	        int temp = nums[i];
	        while(index >= 0 && temp < nums[index]){
	            nums[index+1] = nums[index];
	            index--;
	        }
	        nums[index+1] = temp;
	    }
	}

	//希尔排序 时间复杂度 O(n^1.3) 空间复杂度 O(1)
	void shellSort(vector<int> &nums){
		int size = nums.size();
		for(int gap = size/2; gap > 0; gap /= 2){
			for(int i = gap; i < size; i++){
				int index = i-gap;
				int temp = nums[i];
				while(index > 0 && temp < nums[index]){
					nums[index+gap] = nums[index];
					index -= gap;
				}
				nums[index+gap] = temp;
			}
		}
	}

	void merge(vector<int> &nums, int start, int mid, int end){
		int i = start;
		int j = mid;
		int temp[end-start];
		int index = 0;
		while(i < mid && j < end){
			if(nums[i] < nums[j])
				temp[index++] = nums[i++];
			else
				temp[index++] = nums[j++];
		}
		while(i < mid)
			temp[index++] = nums[i++];
		while(j < mid)
			temp[index++] = nums[j++];
		for(int k = 0; k < index; k++)
			nums[start+k] = temp[k];
	}

	//归并排序 时间复杂度 O(nlogn) 空间复杂度 O(n)
	//参数为左开右闭 [start, end)
	void mergeSort(vector<int> &nums, int start, int end){
		if(end - start < 2)	return
		int mid = (end + start) / 2;
		mergeSort(nums, start, mid);
		mergeSort(nums, mid, end);
		merge(nums, start, mid, end);
	}

	int partition(vector<int> &nums, int start, int end){
		int key = nums[start];
		end--;
		while(start < end){
			while(start < end && nums[end] >= key)
				end--;
			if(start < end)
				nums[start] = nums[end];
			while(start < end && nums[start] <= key)
				start++;
			if(start < end)
				nums[end] = nums[start];
		}
		nums[start] = key;
		return start;
	}

	//快速排序 时间复杂度 O(nlogn) 空间复杂度 O(1)
	//参数为左开右闭 [start, end)
	void quickSort(vector<int> &nums, int start, int end){
		if(end - start < 2)	return;
		int index = partition(nums, start, end);
		quickSort(nums, start, index);
		quickSort(nums, index, end);
	}

	//堆排序 时间复杂度 O(nlogn) 空间复杂度 O(n)
	void heapSort(vector<int> &nums){
		Heap heap = new Heap();
		heap.buildHeap(nums);
		int size = nums.size();
		for(int i = size-1; i >= 0; i--)
			nums[i] = heap.pop();
	}

	//计数排序 时间复杂度 O(n+k) 空间复杂度 O(k)
	//假设数组中最大元素为k
	void countSort(vector<int> &nums, int k){
		int c[k+1];
		for(int i = 0; i < k+1; i++)
			c[i] = 0;
		for(int i = 0; i < nums.size(); i++)
			c[nums[i]]++;
		int index = 0;
		for(int i = 0; i < k; i++){
			for(int j = 0; j < c[k]; j++){
				nums[index++] = i;
			}
		}
	}

	//桶排序 时间复杂度O(n) 空间复杂度O(?)
	void bucketSort(vector<int> &nums, int count){
		int nums_max = nums[0];
		int nums_min = nums[0];
		for(int i = 0; i < nums.size(); i++){
			if(nums[i] < nums_min)
				nums_min = nums[i];
			if(nums[i] > nums_max)
				nums_max = nums[i];
		}
		int gap = (nums_max - nums_min) / 5;
		vector<int> buckets[5];
		for(int i = 0; i < nums.size(); i++)
			bucket[(nums[i] - nums_min) / gap].push_back(nums[i]);
		for(int i = 0; i < 5; i++){
			quickSort(buckets[i], 0, buckets[i].size());
		}
		int index = 0;
		for(int i = 0; i < 5; i++)
			for(int j = 0; j < buckets[i].size(); j++)
				nums[index++] = buckets[i][j];
	}

	//基数排序 时间复杂度(n) 空间复杂度 O(n)
	void radixSort(vector<int> &nums){
		int size = nums.size();
		int nums_max = nums[0];
		for(int i = 0; i < size; i++)
			if(nums_max < nums[i])
				nums_max = nums[i];
		int radix = 1;
		while(nums_max /= 10)
			radix++;
		for(int k = 0; k < radix; k++){
			vector<int> radixes[10];
			for(int i = 0; i < size; i++)
				radixes[nums[i]/(pow(10, k)%10)].push_back(nums[i]);
			int index = 0;
			for(int i = 0; i < 10; i++)
				for(int j = 0; j < radixes[i].size(); j++)
					nums[index++] = radixes[i][j];
		}
	}
}