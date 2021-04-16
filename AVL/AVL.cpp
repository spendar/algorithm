class AVL{

private:
	Node* root;

	void leftRotate(Node* &node){
		Node* right = node->right;
		node->right = right->left;
		right->left = node;
		node = right;
	}
	 
	void rightRotate(Node* &node){
		Node* left = node->left;
		node->left = left->right;
		left->right = node;
		node = left;
	}

public:

	struct Node{
		int val;//节点保存的值
		Node* left;//左子树
		Node* right;//右子树
		int height;//以该节点为根的树的高度
	    Node(int val) : val(val), left(NULL), right(NULL), height(1) {}
	}

	AVL(): root(NULL){}


	//AVL查找元素的递归版本
	// Node* search(Node* node, int target){
	// 	if(node == NULL)	return NULL;
	// 	if(target == node->val)
	// 		return node;
	// 	else if(target > node->val)
	// 		return search(node->right, target);
	// 	else
	// 		return search(node->left, target);
	// }

	//AVL查找元素的非递归版本
	Node* search(Node* node, int target){
		if(node == NULL)	return node;
		Node* cur = node;
		while(cur){
			if(target == node->val)
				return cur;
			else if(target > node->val)
				cur = cur->right;
			else
				cur = cur->left;
		}
		return cur;
	}

	 
	bool insert(Node* node, int val){
		//节点为空则直接插入
		if(node == NULL){
			node = new Node(val);
			return true;
		}
		//插入值已存在，则返回插入错误
		if(node->val == val)
			return false;
		else if(node->val > val){
			if(insert(node->left, val)){
				//更新节点高度
				updateHeight(node);
				//由于是往左子树插入，因此当平衡因子异常时只能变为2
				if(getBanlancedFactor(node) == 2){
					int factor = getBanlancedFactor(node->left);
					if(factor == 1){
						//情况1：父节点平衡因子为1，祖父节点为2
						//右旋中间节点
						rightRotate(node);
					}else if(factor == -1){
						//情况2：父节点平衡因子为-1，祖父节点为2
						//左旋底层节点，再右旋中间节点
						leftRotate(node->left);
						rightRotate(node);
					}
				}
				return true;
			}else
				return false;
		}else{
			if(insert(node->right, val)){
				//更新节点高度
				updateHeight(node);
				//由于是往右子树插入，因此当平衡因子异常时只能变为-2
				if(getBanlancedFactor(node) == -2){
					int factor = getBanlancedFactor(node->left);
					if(factor == 1){
						//情况3：父节点平衡因子为1，祖父节点为-2
						//右旋底层节点，再左旋中间节点
						rightRotate(node->right);
						leftRotate(node);
					}else if(factor == -1){
						//情况4：父节点平衡因子为-1，祖父节点为-2
						//左旋中间节点
						leftRotate(node);
					}
				}
				return true;
			}else
				return false;
		}
	}

	bool erase(Node* &node, int val){
		if(node == NULL)	return false;
		if(node->val == val){
			delete node;
			node = NULL;
			return true;
		}else if(node->val < val){
			if(erase(node->right), val){
				//更新节点高度
				updateHeight(node);
				//由于是从右子树删除，因此当平衡因子异常时只能变为2
				if(getBanlancedFactor(node) == 2){
					int factor = getBanlancedFactor(node->left);
					if(factor == -1){
						//情况2：父节点平衡因子为-1，祖父节点为2
						//左旋底层节点，再右旋中间节点
						leftRotate(node->left);
						rightRotate(node);
					}else if(factor == 1){
						//情况1：父节点平衡因子为1，祖父节点为2
						//右旋中间节点
						rightRotate(node);
					}
				}
				return true;
			}else
				return false;
		}else{
			if(erase(node->left), val){
				//更新节点高度
				updateHeight(node);
				//由于是从左子树删除，因此当平衡因子异常时只能变为-2
				if(getBanlancedFactor(node) == -2){
					int factor = getBanlancedFactor(node->left);
					if(factor == -1){
						//情况4：父节点平衡因子为-1，祖父节点为-2
						//左旋中间节点
						leftRotate(node);
					}else if(factor == 1){
						//情况3：父节点平衡因子为1，祖父节点为-2
						//右旋底层节点，再左旋中间节点
						rightRotate(node->left);
						leftRotate(node);
					}
				}
				return true;
			}else
				return false;
		}
	}
}