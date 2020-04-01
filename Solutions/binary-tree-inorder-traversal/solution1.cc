#include <stack>                  
                                                           
template <class T, class Container>
auto pop(std::stack<T, Container> &s) {
    auto ret = s.top();           
    s.pop();
    return ret;                  
}                                            
                                                           
/**                                                                                                                    
 * Precondition: root != nullptr and the tree is BST
 */                                                        
auto BST_to_array(TreeNode *root) -> vector<int> {
    vector<int> ret;           
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
            ret.push_back(node->val);  
               
            // Explore right-node
            node = node->right;              
        } while (node == nullptr);                                                                                     
    } while (true);                                                                                                    
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
    vector<int> inorderTraversal(TreeNode* root) {
        if (root != nullptr)
            return BST_to_array(root);
        else
            return vector<int>();
    }
};
