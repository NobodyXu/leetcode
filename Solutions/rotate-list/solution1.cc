#include <utility>

/**
  * Returns the (k - 1) th node and the last node of the list.
  * 
  * If k > len_of_list, k = k % len_of_list
  */
auto find_kth_node_from_end(ListNode *head, int k) -> std::pair<ListNode*, ListNode*> {
    ;
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
        auto [k_minus_1, last] = find_kth_node_from_end(head, k);
        auto kth = k_minus_1->next;
        
        // Let kth become the new head
        // and link head after last
        last->next = head;
        // Make k_minus_1 become the new last
        k_minus_1->next = nullptr;
        
        return kth;
    }
};
