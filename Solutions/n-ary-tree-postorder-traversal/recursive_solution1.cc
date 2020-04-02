/**
 * Runtime: 40 ms, faster than 94.31% of C++ online submissions for N-ary Tree Postorder Traversal.
 * Memory Usage: 11.2 MB, less than 100.00% of C++ online submissions for N-ary Tree Postorder Traversal.
 */
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

void postorder_impl(vector<int> &ret, const Node *node)
{
    for (const auto *each: node->children)
        postorder_impl(ret, each);
    
    ret.push_back(node->val);
}

class Solution {
public:
    vector<int> postorder(Node* root)
    {
        vector<int> ret;
        
        if (root != nullptr)
            postorder_impl(ret, root);
        
        return ret;
    }
};
