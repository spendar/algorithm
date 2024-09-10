/*
 * @Author: spendar
 * @Date: 2024-08-28 22:30:01
 * @LastEditors: spendar
 * @LastEditTime: 2024-09-10 10:25:01
 * @FilePath: /algorithm/IntervalTree/binaryindextree.cpp
 * @Description: to implement binary index tree 
 * @Scene: 单点修改，区间查询
 */

#include <vector>

using namespace std;

class BinaryIndexTree {
private:
    vector<int> data, index;
    int lowbit(int x) {
        return x & (-x);
    }
    int sum(int idx) {
        int res = 0;
        idx++;
        for(int i = idx; i; i -= lowbit(i)) {
            res += index[i];
        }
        return res;
    }
public:
    BinaryIndexTree(vector<int> nums) {
        data.push_back(0);
        index.push_back(0);
        int size = nums.size();
        vector<int> sum(size+1);
        for(int i = 0; i < size; i++) {
            data.push_back(nums[i]);
            sum[i+1] = sum[i] + nums[i];
            index[i+1] = sum[i+1] - sum[i+1-lowbit(i+1)];
        }
    }

    void add(int idx, int val) {
        data[idx] += val;
        for(int i = idx+1; i < data.size(); i++) {
            index[i] += val;
        }
    }

    int search(int left, int right) {
        return sum(right) - sum(left);
    }
};