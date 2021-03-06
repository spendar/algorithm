#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : val(val), left(NULL), right(NULL) {}
};

class TreeTraverse{
public:
    void preOrder(TreeNode* node) {
        if(!node) {
            return;
        }
        cout<<node->val<<" ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(TreeNode* node) {
        if(!node) {
            return;
        }
        inOrder(node->left);
        cout<<node->val<<" ";
        inOrder(node->right);
    }

    void postOrder(TreeNode* node) {
        if(!node) {
            return;
        }
        postOrder(node->left);
        cout<<node->val<<" ";
        postOrder(node->right);
    }

    void preOrderPlus(TreeNode* root) {
        if(!root) {
            return;
        }
        stack<TreeNode*> s;
        s.push(root);
        while(!s.empty()) {
            TreeNode* node = s.top();
            s.pop();
            cout<<node->val<<" ";
            if(node->right) {
                s.push(node->right);
            }
            if(node->left) {
                s.push(node->left);
            }
        }
    }

    void inOrderPlus(TreeNode* root) {
        if(!root) {
            return;
        }
        TreeNode* cur = root;
        stack<TreeNode*> s;
        while(cur != NULL || !s.empty()) {
            if(cur) {
                while(cur) {
                    s.push(cur);
                    cur = cur->left;
                }
            } else {
                cur = s.top();
                s.pop();
                cout<<cur->val<<" ";
                cur = cur->right;
            }
        }
    }

    void postOrderPlus(TreeNode* root) {
        if(!root) {
            return;
        }
        stack<TreeNode*> s;
        s.push(root);
        while(!s.empty()) {
            TreeNode* node = s.top();
            s.pop();
            cout<<node->val<<" ";
            if(node->left) {
                s.push(node->left);
            }
            if(node->right) {
                s.push(node->right);
            }
        }
        // ???????????????????????? ???-???-????????????reverse()????????????????????? ???-???-????????????????????????
    }
};