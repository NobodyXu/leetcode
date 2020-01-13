/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    void advance(ListNode* &node) {
        node = node->next;
    }
    
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *ret = nullptr;     
        ListNode **next = &ret;
        
        switch (unsigned{l1 == nullptr} << 1 | unsigned{l2 == nullptr}) {
            case 2:
                return l2;
            
            case 1:
                return l1;

            case 0:
                 do {
                    if (l1->val < l2->val) {
                        *next = l1;
                        advance(l1);

                        if (l1 == nullptr) {
                            (*next)->next = l2;
                            break;
                        }
                    } else {
                        *next = l2;
                        advance(l2);
                        
                        if (l2 == nullptr) {
                            (*next)->next = l1;
                            break;
                        }
                    }
                     
                    next = &(*next)->next;
                } while (true);
         
            case 3:
                ;
        }
        
        return ret;
    }
};
