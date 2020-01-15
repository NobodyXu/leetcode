#include <cstddef>
#include <thread>
#include <memory>

template <class T>
class forward_list {
    ;
};

template <class T>
class queue {
    using Container_t = forward_list<T>;
    using iterator = typename Container_t::
    Container_t data;
    
};

template <class Function, class ...Args>
class Thread_pool {
    static auto get_cores() noexcept {
        if (std::thread::hardware_concurrency != 0)
            return std::thread::hardware_concurrency;
        else
            return 1;
    }
    
    static void execute_tasks(Thread_pool &pool) {
        ;
    }
    
    std::size_t pool_size;
    std::unique_ptr<std::thread[]> threads;
    
    Function func;
    
public:
    Thread_pool(const Function &f):
        Thread_pool(f, get_cores())
    {}
    
    Thread_pool(const Function &f, std::size_t cores):
        pool_size{cores},
        threads{new std::thread[cores]},
        func{f}
    {
        for (std::size_t i = 0; i != pool_size; ++i)
            threads[i] = std::thread(&execute_tasks, *this);
    }
    
    void addTask(Function &&f, Args &&...args) {
        ;
    }
       
    ~Thread_pool() {
        /* Close the queue */;
        
        for (std::size_t i = 0; i != pool_size; ++i)
            threads[i].join();
    }
};

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
        
        // First Solution
        ListNode *ret = lists.front();
        
        for (auto it = lists.begin() + 1; it != lists.end(); ++it)
            ret = merge2Lists(ret, *it);
        
        return ret;
    }
};
