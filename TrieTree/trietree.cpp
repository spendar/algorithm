struct TreeNode{
	TreeNode* child[26];
}

//以一个字符串作为字典树的示范说明
class TrieTree{
private:
	TreeNode* root;

public:
	TrieTree(){
		root = new TreeNode();
	}

	void insert(string s){
		TreeNode* cur = root;
		for(char c : s){
			cur->child[c-'0'] = new TreeNode();
			cur = cur->child[c-'0'];
		}
	}

	bool search(string s){
		TreeNode* cur = root;
		for(char c : s){
			if(cur->child[c-'0'])
				cur = cur->child[c-'0'];
			else
				return false;
		}
		return true;
	}
}