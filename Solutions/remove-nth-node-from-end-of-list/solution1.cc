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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode **before_nth = &head;
        ListNode *tail = head;
        
        // Forward tail n nodes
        for (int i = 0; i != n; ++i)
            tail = tail->next;
        
        while (tail != nullptr) {
            tail = tail->next;
            before_nth = &(*before_nth)->next;
        }
        *before_nth = (*before_nth)->next;
        
        return head;
    }        

};
