/**
 * Runtime: 0 ms, faster than 100.00% of C++ online submissions for Binary Tree Postorder Traversal.
 * Memory Usage: 7 MB, less than 100.00% of C++ online submissions for Binary Tree Postorder Traversal.
 */
#include <stack>

#include <type_traits>
#include <cstdint>

template <class Ptr, class T>
class Tup {
    static_assert(sizeof(Ptr) == 8);
    static_assert(sizeof(T) <= 2);
    static_assert(is_integral_v<T>);
    
    using type = std::uintptr_t;
    
    static constexpr const auto mask = (type{1} << 48) - 1;
    
    type value;
    
public:
    Tup(const Ptr &p, const T &obj) noexcept:
        value{reinterpret_cast<type>(p) | (static_cast<type>(obj) << 48)}
    {}
    
    Ptr first() const noexcept
    {
        return reinterpret_cast<Ptr>(value & mask);
    }
    
    auto& second() noexcept
    {
        return *reinterpret_cast<T*>(reinterpret_cast<char*>(&value) + 6);
    }
};

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
        
        std::stack<Tup<TreeNode*, unsigned char>> stack;
        auto *node = root;
        unsigned char index;
        for (; ;) {
            do {
                stack.emplace(node, 1);
                node = node->left;
            } while (node != nullptr);
            
            // Now we are at left-most node
            node = stack.top().first();
            index = stack.top().second();
            while (node->right == nullptr || index == 2) {
                ret.emplace_back(node->val);
                stack.pop();
                
                if (stack.size() == 0)
                    return ret;
                
                node = stack.top().first();
                index = stack.top().second();
            }
            
            stack.top().second() = 2;
            node = node->right;
        }
    }
};
