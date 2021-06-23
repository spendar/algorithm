#include<vector>

using namespace std;

const int maxn = 100;

class Heap{

private:
	int len;
	int array[maxn+1];

public:

	Heap(): len(0){};

	bool isEmpty(){
		return !len;
	}

	void upAdjust(int index){
		int i = index;
		int j = index / 2;
		while(j > 0){
			if(array[i] > array[j]){
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
				i = j;
				j = i / 2;
			}else
				break;
		}
	}

	void downAdjust(int index){
		int i = index;
		int j = i * 2;
		while(j <= len){
			if(j+1 <= len && array[j+1] > array[j])
				j++;
			if(array[i] < array[j]){
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
				i = j;
				j = i * 2;
			}else
				break;
		}
	}

	void insert(int x){
		if(len == maxn){
			cout<<"堆空间已满，无法插入";
			return;
		}
		array[++len] = x;
		upAdjust(len);
	}

	int pop(){
		int temp = array[1];
		array[1] = array[len--];
		downAdjust(1);
		return temp;
	}

	void buildHeap(vector<int> nums){
		for(int i = 0; i < nums.size(); i++){
			if(len == maxn){
				cout<<"堆空间已满，无法插入";
				return;
			}
			len++;
			array[len] = nums[i];
			upAdjust(1, len);
		}
	}
}