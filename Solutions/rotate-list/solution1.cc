#include <utility>

/**
  * Returns the ptr to kth ListNode**, which points to the member next of previous node or points to (ListNode*) head, and the last node of the list.
  * 
  * If k > len_of_list, k = k % len_of_list
  * 
  * Precondition: 0 < k
  */
auto find_kth_node_from_end(ListNode **head_p, int k) -> std::pair<ListNode**, ListNode*> {
    ListNode *prev;
    ListNode *curr = *head_p;
    
    int i = 0;
    for (; curr != nullptr && i != k; prev = curr, curr = curr->next, ++i);
    
    if (i == k) {
        // Go on and calculate (k - 1)th and the last node.
        ListNode **kth_ptr = head_p;
        
        // Consume the list
        for (; curr != nullptr; prev = curr, curr = curr->next)
            kth_ptr = &(*kth_ptr)->next;
        
        return {kth_ptr, prev};
    } else {
        auto size = i;
        auto new_k = k % i;
        
        if (new_k == 0)
            return {head_p, prev};
        
        // tail call optimization shall apply here so that no additional stack space is occupied
        return find_kth_node_from_end(head_p, new_k);
    }
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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr || head->next == nullptr || k == 0)
            return head;
        
        // kth_ptr == &(k - 1)th->next
        auto [kth_ptr, last] = find_kth_node_from_end(&head, k);
        
        if (kth_ptr == &head) // When k == len_of_list
            return head;
        
        auto kth = *kth_ptr;
        
        // Let kth become the new head
        // and link head after last
        last->next = head;
        // Make k_minus_1 become the new last
        *kth_ptr = nullptr;
        
        return kth;
    }
};
