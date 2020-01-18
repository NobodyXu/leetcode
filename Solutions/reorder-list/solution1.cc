#include <cstddef>
#include <cstdint>
#include <utility>

/**
 * Precondition: head != nullptr
 */
auto size(ListNode *head) -> std::size_t {
    std::size_t len = 0;
    do {
        head = head->next;
        ++len;
    } while (head != nullptr);
    
    return len;
}

/**
 * Returns (odd_part, even_part), which both != nullptr
 * 
 * If len is even, then odd_part and even_part is of the same size.
 * Otherwise, odd_part = even_part + 1
 */
auto split_in_half(ListNode *head, std::size_t len) -> std::pair<ListNode*, ListNode*> {
    ListNode *first_odd_part = head;
    ListNode *last_odd_part = head;
    
    auto odd_part_len = (len >> 1) + (len & 1); // len / 2 + len % 2
    for (std::size_t i = 0; i != (odd_part_len - 1); ++i)
        last_odd_part = last_odd_part->next;
    
    ListNode *first_even_part = last_odd_part->next;
    last_odd_part->next = nullptr;
    
    return {first_odd_part, first_even_part};
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
            auto [odd_part, even_part] = split_in_half(head, size(head));
            return merge(odd_part, reverse(even_part));
        }
    }
};
