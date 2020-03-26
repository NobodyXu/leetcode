#include <iterator>

ListNode* merge2Lists(ListNode *x, ListNode *y) {
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

/**
 * lists.size() > 1
 */
ListNode* merge_sort(vector<ListNode*> &lists) {
    auto beg = lists.begin();
    auto end = lists.end();
    
    do {
        auto out = beg;
        auto it  = beg + 1;
        
        for (; it < end; std::advance(it, 2), ++out)
            *out = merge2Lists(*std::prev(it), *it);
        
        if (--it != end) {
            *out = *it;
            end = std::next(out);
        } else
            end = out;
    } while (std::distance(beg, end) > 1);
    
    return *beg;
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0)
            return nullptr;
        else if (lists.size() == 1)
            return lists[0];
        else
            return merge_sort(lists);
    }
};
