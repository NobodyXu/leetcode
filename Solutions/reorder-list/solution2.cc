#include <array>

#include <cstddef>
#include <cstdint>
#include <utility>

struct SkipNode {
    ListNode *node_ptr;
    std::size_t index;
};


/**
  * Returns (odd_part, even_part), which both != nullptr
  * 
  * If size() is even, then odd_part and even_part is of the same size.
  * Otherwise, odd_part = even_part + 1
  * 
  * Internally, it utilizes the concept of skip list to calculate the middle point 
  * quickly.
  * 
  * Best case O(1), Worst case O().
  */
auto split_in_half(ListNode *head) -> std::pair<ListNode*, ListNode*> {
    std::size_t len = 0;
    
    // Every `diff` nodes, a SkipNode will be created
    // They will be used to find the middle point
    static constexpr const std::size_t init_diff = 10;
    std::size_t diff = init_diff;
    
    std::array<SkipNode, init_diff * 2> skipNodes;
    std::size_t index = 0;
    
    auto it = head;
    do {
        if (len % diff == 0)
            skipNodes[(index++) % skipNode.size()] = SkipNode{it, len};
            
        // Increment
        ++len;
        it = it->next;
    } while (it != nullptr);
    
    return {head, };
}

/**
 * Precondition: odd_part, even_part != nullptr
 */
void merge(ListNode *odd_part, ListNode *even_part) {
    auto prev_odd = odd_part;
    auto curr_even = even_part;
    
    /*
     * if len of the original list is even, then
     * 
     *     the two part is of the same size.
     *     Because the odd part is forwarded once before the loop, so the odd part should reach
     *     the nullptr faster than the even part.
     *
     * else, then
     * 
     *     the size of odd part = the size of even part + 1.
     *     Due to the forward of odd before the loop, 
     *     the size of odd part = the size of even part at the beginning of the loop.
     *     So they shall reach the end at the same iteration.
     * 
     * fi
     * 
     * So there is not need for testing the end condition of the 2 parts, only the odd part will suffice.
     */
    for (; prev_odd->next != nullptr; ) {
        auto curr_odd = prev_odd->next;
        auto next_even = curr_even->next;
        
        // Insert curr_even after prev_odd, before curr_odd
        prev_odd->next = curr_even;
        curr_even->next = curr_odd;
        
        // Increment
        curr_even = next_even;
        prev_odd = curr_odd;
    }
    
    // Since either both parts meets the end condition or only the odd part meets,
    // let's put the rest nodes of the even part after the last node of the curr part.t
    prev_odd->next = curr_even;
}

auto reverse(ListNode *head) -> ListNode* {
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
    void reorderList(ListNode* head) {
        if (head != nullptr && head->next != nullptr && head->next->next != nullptr) {
            auto [odd_part, even_part] = split_in_half(head);
            return merge(odd_part, reverse(even_part));
        }
    }
};
