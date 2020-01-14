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
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        
        ListNode *prev = head;
        ListNode *curr = head->next;
        
        // Set the last node
        prev->next = nullptr;
        
        do {
            ListNode *next = curr->next;
            curr->next = prev;
            
            prev = curr;
            curr = next;
        } while (curr != nullptr);
        
        return prev;
    }
};
