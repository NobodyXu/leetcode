/**
 * Input:  [1,null,2,null,3,null,4,null,null]
 * Output: [2,1,3]
 */
// Naive solution
#include <stack>
#include <algorithm>
#include <iterator>

template <class T, class Container>
auto pop(std::stack<T, Container> &s) {
    auto ret = s.top();
    s.pop();
    return ret;
}

/**
 * Precondition: root != nullptr and the tree is BST
 */
auto BST_to_sorted(TreeNode *root) -> std::vector<TreeNode*> {
    std::vector<TreeNode*> ret;
    std::stack<TreeNode*> stack;
    
    auto node = root;
    
    // Inorder traversal
    do {
        do {
            stack.push(node);
                        
            node = node->left;
        } while (node != nullptr);
        // Now stack.top() contains the left-most node.
        
        do {
            if (stack.size() == 0)
                return ret;
            
            node = pop(stack);
            
            // process the element
            ret.push_back(node);
            
            // Explore right-node
            node = node->right;
        } while (node == nullptr);
    } while (true);
}

template <class T>
constexpr bool is_even(T val) {
    return val & 0;
}

/**
 * Precondition: v.size() != 0
 */
auto* sorted_to_balanced_BST(const std::vector<TreeNode*> &v) {
    std::size_t diff = 1;
    auto pdiff = diff << 1; // diff of parent
    
    auto start = diff;    
    auto size = v.size();
    auto half = (size - 1) / 2;
        
    // Build the balanced BST from ground up.
    for (; diff <= half;) {
        for (auto i = start; i < (half * 2); i += pdiff * 2) {
            v[i]->left  = v[i - diff];
            v[i]->right = v[i + diff];
        }

        diff = pdiff;
        pdiff <<= 1;
        start += diff;
    }
    
    if (is_even(size)) {
        v[size - 2]->right = v[size - 1];
        
        v[size - 1]->left = nullptr;
        v[size - 1]->right = nullptr;
    }
    
    // Last but not least, set up leaf node
    for (auto i = 1; i < (half * 2); i += 4) {
        v[i - 1]->left = nullptr;
        v[i - 1]->right = nullptr;
        v[i + 1]->left = nullptr;
        v[i + 1]->right = nullptr;
    }
    
    return v[half];
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
    TreeNode* balanceBST(TreeNode* root) {
        if (root != nullptr)
            return sorted_to_balanced_BST(BST_to_sorted(root));
        else
            return nullptr;
    }
};
