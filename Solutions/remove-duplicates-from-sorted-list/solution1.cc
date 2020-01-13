auto find_not(ListNode *beg) -> ListNode* {
    const auto &value = beg->val;
    
    auto it = beg;
    do {
        it = it->next;
    } while (it != nullptr && it->val == value);
    
    return it;
}

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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *it = head;
        
        while (it != nullptr) {
            ListNode *new_it = find_not(it); // The first node that differs
            it->next = new_it; // Removes all nodes between them.
            it = new_it; // Increment iterator
        }
        
        return head;
    }
};
