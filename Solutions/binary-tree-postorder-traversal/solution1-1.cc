/**
 * Runtime: 0 ms, faster than 100.00% of C++ online submissions for Binary Tree Postorder Traversal.
 * Memory Usage: 7 MB, less than 100.00% of C++ online submissions for Binary Tree Postorder Traversal.
 */

#include <stack>

#include <type_traits>
#include <cstdint>

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        
        if (root == nullptr)
            return ret;
        
        std::stack<TreeNode*> stack;
        auto *node = root;
        unsigned char index;
        for (; ;) {
            do {
                stack.push(node);
                node = node->left;
            } while (node != nullptr);
            
            // Now we are at left-most node
            TreeNode *prev_node = nullptr;
            
            node = stack.top();
            while (node->right == nullptr || node->right == prev_node) {
                ret.emplace_back(node->val);
                stack.pop();
                
                if (stack.size() == 0)
                    return ret;
                
                prev_node = node;
                node = stack.top();
            }
            node = node->right;
        }
    }
};
