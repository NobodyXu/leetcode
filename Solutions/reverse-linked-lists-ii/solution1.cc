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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *ret = head;
        ListNode **before_start = &ret;
        
        for (int i = 1; i < m; ++i)
            before_start = &(*before_start)->next;
        
        ListNode *new_last_node = *before_start;
        
        ListNode *prev = *before_start;
        ListNode *curr = prev->next;
        
        for (int i = m; i != n; ++i) {
            auto next = curr->next;
            curr->next = prev;
            
            // Increment
            prev = curr;
            curr = next;
        }
        
        *before_start = prev;
        new_last_node->next = curr;
        
        return ret;
    }
};
