#include <vector>
#include <stack>
#include <utility> // For std::swap

template <class Stack, class T>
auto& push_if_not_null(Stack &stack, T &&val) {
    if (val != nullptr)
        stack.push(val);
    return stack;
}

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
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr))
            return root;
        
        std::stack<TreeNode*, std::vector<TreeNode*>> stack;
        stack.push(root);
        
        do {
            auto it = stack.top();
            stack.pop();
            
            std::swap(it->left, it->right);
            
            if (it->left != nullptr)
                stack.push(it->left);
            if (it->right != nullptr)
                stack.push(it->right);
        } while (!stack.empty());
        
        return root;
    }
};
