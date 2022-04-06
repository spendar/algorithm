#include <vector>
#include <iostream>
#include <string.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
private:
	vector<string> ans;
	vector<string> temp;
	void backtrack(string& s, int index, string& str) {
		if(index == s.length()) {
			if(temp.size() == 4) {
				string ss = "";
				for(int i = 0; i < 4; i++) {
					ss.append(temp[i]);
					if(i < 3) {
						ss.push_back('.');
					}
				}
				ans.push_back(ss);
			}
			return;
		}
		if(temp.size() > 4) {
			return;
		}
		if(str != "0" && (str == "" || (10 * stoi(str) + s[index]-'0') <= 255)) {
			str.push_back(s[index]);
			backtrack(s, index+1, str);
			str.pop_back();
		}
        if(str != "") {
            temp.push_back(str);
            str = "";
            str.push_back(s[index]);
            backtrack(s, index+1, str);
            str = temp.back();
            temp.pop_back();
        }
	}
public:
    vector<string> restoreIpAddresses(string s) {
    	if(s.length() < 4 || s.length() > 12) {
    		return ans;
    	}
        string str = "";
    	backtrack(s, 0, str);
    	return ans;
    }
};



int main() {
    Solution* s = new Solution();
    auto a = s->restoreIpAddresses("25525511135");
    return 0;
}