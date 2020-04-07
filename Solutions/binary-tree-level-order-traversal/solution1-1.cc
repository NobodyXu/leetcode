/**
 * Runtime: 4 ms, faster than 93.26% of C++ online submissions for 
 * Binary Tree Level Order Traversal.
 * Memory Usage: 11.6 MB, less than 100.00% of C++ online submissions for 
 * Binary Tree Level Order Traversal.
 */

#include <utility>

auto& push_nonnull(vector<TreeNode*> &v, TreeNode *node)
{
    if (node != nullptr)
        v.push_back(node);
    return v;
}

vector<vector<int>> levelOrder_impl(TreeNode *root)
{
    vector<vector<int>> ret;
    
    vector<TreeNode*> buffer;
    vector<int> values;
    vector<TreeNode*> next_buffer;
    
    buffer.push_back(root);
    do {
        values.reserve(buffer.size());
        for (auto *node: buffer) {
            values.push_back(node->val);
            push_nonnull(push_nonnull(next_buffer, node->left), node->right);
        }
        
        ret.push_back(std::move(values));
        
        buffer.swap(next_buffer);
        next_buffer.clear();
        //buffer = std::move(next_buffer);
    } while (buffer.size() != 0);
    
    return ret;
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
    vector<vector<int>> levelOrder(TreeNode* root)
    {
        if (root != nullptr)
            return levelOrder_impl(root);
        else
            return {};
    }
};
