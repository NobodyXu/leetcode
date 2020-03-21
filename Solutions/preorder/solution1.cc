#include <stack>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    std::stack<TreeNode*> stack;
    
    void push(TreeNode *node) {
        if (node != nullptr)
            stack.push(node);
    }
    
    auto pop() {
        auto ret = stack.top();
        stack.pop();
        return ret;
    }
    
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        
        push(root);
        while (stack.size() != 0) {
            auto node = pop();
            push(node->right);
            push(node->left);
            
            ret.push_back(node->val);
        }
        
        return ret;
    }
};
