/*
 * @Author: spendar
 * @Date: 2024-10-27 23:12:20
 * @LastEditors: spendar
 * @LastEditTime: 2024-10-27 23:20:56
 * @FilePath: /algorithm/UnionFindSet/unionfindset.cpp
 * @Description: To implement UnionFindSet
 */
#include <vector>

using namespace std;

class UnionFindSet {
private:
    int size;
    vector<int> data;
public:
    UnionFindSet(int n) {
        size = n;
        data.resize(n);
        for(int i = 0; i < n; i++) {
            data[i] = i;
        }
    }

    int Find(int idx) {
        if(idx != data[idx]) {
            data[idx] = Find(data[idx]);
            return data[idx];
        } else {
            return idx;
        }
    }

    bool Union(int a, int b) {
        int fa = Find(a);
        int fb = Find(b);
        if(fa == fa) {
            return false;
        }
        data[fb] = fa;
    }
};