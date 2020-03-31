/**
 * AddressSanitizer:DEADLYSIGNAL
 * =================================================================
 * ==32==ERROR: AddressSanitizer: stack-overflow on address 0x7ffd9aa4bff8 (pc 0x0000003e9fd9 bp 0x7ffd9aa4c010 sp 0x7ffd9aa4c000 T0)
 * ==32==ABORTING
 */
// Naive solution
#include <stack>
#include <algorithm>
#include <iterator>

// headers for assert_sorted
//#include <err.h>

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

/*
auto& assert_sorted(const std::vector<TreeNode*> &v) {
    auto it = is_sorted_until(v.begin(), v.end(), [](const auto &x, const auto &y) {
        return x->val < y->val;
    });
    
    auto diff = v.end() - it;
    if (diff > 0)
        err(1, "There are %zd elements unsorted, counted backwards", diff);
        
    return v;
}*/

template <class T>
constexpr bool is_odd(T val) {
    return val & 1;
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
    
    for (; diff <= half;) {
        for (auto i = start; i < (half * 2); i += pdiff * 2) {
            v[i]->left  = v[i - diff];
            v[i]->right = v[i + diff];
        }

        diff = pdiff;
        pdiff <<= 1;
        start += diff;
    }

    if (is_even(size))
        v[size - 2]->right = v[size - 1];

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
