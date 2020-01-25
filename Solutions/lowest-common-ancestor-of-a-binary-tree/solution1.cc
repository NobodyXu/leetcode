#include <cstdint>

#include <vector>
#include <algorithm>

/**
 * This function iterate over tree in preorder.
 * 
 * @root must not be nullptr
 * @Function should be a callable object, with interface
 * 
 *     //
 *     // @stack records all the nodes in the path to the current node
 *     //        the current node == path.back().
 *     // 
 *     // @Return returns whether it is necessary to continuing iterating over
 *     //         the nodes in the tree.
 *     //
 *     bool (const std::vector<TreeNode*> &path);
 */
template <class Function>
void find_node(TreeNode *root, Function &&f) {
    std::vector<TreeNode*> path;
    // stack 'points' to all nodes who has both left and right leaves and
    // there right leaves haven't been explored.
    // 
    // stack will always in ascending order.
    std::vector<std::size_t> stack;
    
    auto *curr = root;
    while (true) {
        path.push_back(curr);
        if (!f(path))
            break;
        
        switch ((uint8_t{curr->left != nullptr} << 1) | uint8_t{curr->right != nullptr}) {
            case 3: // curr->left != nullptr && curr->right != nullptr
                stack.push_back(path.size());
                curr = curr->left;
                break;
                
            case 2: // curr->left != nullptr && curr->right == nullptr
                curr = curr->left;
                break;
                
            case 0: // curr->left == nullptr && curr->right == nullptr
                if (stack.empty())
                    return;
                    
                path.resize(stack.back());
                stack.pop_back();
                
                curr = path.back();
                
            case 1: // curr->left == nullptr && curr->right != nullptr
                curr = curr->right;
        }
    }
}

/**
 * @class It should be RandomAccessIterator.
 */
template <class It>
auto last_match(It first1, It last1, It first2, It last2) {
    // Due to the fact that std::mismtach is not safe for different size until
    // C++14, handle it here.
    auto size = std::min(last1 - first1, last2 - first2);
    
    auto [it1, it2] = std::mismatch(first1, first1 + size, 
                                    first2);
    
    return --it1;
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == p || root == q)
            return root;
        
        std::vector<TreeNode*> path_to_p, path_to_q;
        
        // Iterate over the tree to find p and q
        find_node(root, [&](const std::vector<TreeNode*> &path) {
            if (path.back()->val == p->val)
                path_to_p = path;
            if (path.back()->val == q->val)
                path_to_q = path;
                
            if (!path_to_p.empty() && !path_to_q.empty())
                return false;
            return true;
        });
        
        return *last_match(path_to_p.begin(), path_to_p.end(), 
                           path_to_q.begin(), path_to_q.end());
    }
};
