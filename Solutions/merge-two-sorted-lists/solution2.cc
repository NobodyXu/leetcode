/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* x, ListNode* y) {
        if (x == nullptr)
            return y;
        if (y == nullptr)
            return x;
    
        ListNode *ret = x;
    
        // next_p points to the member (ListNode*) next of previous node,
        // which points to the current node.
        for (ListNode **next_p = &ret; ; ) {
            auto *curr = *next_p;
            if (curr->val > y->val) {
                auto next_y = y->next;
            
                // Add y before curr, so that (*next_p)->val <= curr->va;
                y->next = curr;
                *next_p = y;
            
                y = next_y;
            
                if (y == nullptr)
                    break;
            }
        
            next_p = &(*next_p)->next;
            if (*next_p == nullptr) {
                *next_p = y;
                break;
            }
        }
    
        return ret;
    }
};
