class Sort{

	//冒泡排序 O(n^2)
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

	//选择排序 O(n^2)
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

	//插入排序 O(n^2)
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

	//希尔排序 O(n^1.3)
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

	//归并排序 O(nlogn)
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

	//快速排序 O(nlogn)
	//参数为左开右闭 [start, end)
	void quickSort(vector<int> &nums, int start, int end){
		if(end - start < 2)	return;
		int index = partition(nums, start, end);
		quickSort(nums, start, index);
		quickSort(nums, index, end);
	}
}