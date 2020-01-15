#include <cstddef>
#include <utility>
#include <optional>

#include <thread>
#include <memory>
#include <atomic>

struct forwardListNode_base {
    std::atomic<forwardListNode_base*> next = nullptr;
};

template <class T>
class Forward_list {
    struct Node: public forwardListNode_base {
        T obj;
        
        template <class ...Args>
        Node(Args &&...args):
            forwardListNode_base{},
            obj{std::forward<Args>(args)...}
        {}
    };
    
    forwardListNode_base before_start;
    forwardListNode_base *last = nullptr;
    
public:
    Forward_list() = default
    
    Forward_list(const Forward_list&) = delete;
    Forward_list(Forward_list&&) = delete;
    
    Forward_list& operator = (const Forward_list&) = delete;
    Forward_list& operator = (Forward_list&&) = delete;
    
    /**
      * Try to pop front element.
      * If failed, then return no objects.
      */
    std::optional<T> pop_front() noexcept {
        ;
        
        // Need to update last
    }
    
    template <class ...Args>
    void emplace_back(Args &&...args) {
        auto new_node = Node{std::forward<Args>(args)...};
        
        if (last == nullptr) {
            ;
        }
        
        forwardListNode *end = nullptr;
        while (last->next.compare_exchage_weak(end, &new_node)) {
            // Wait for last to be updated;
            end = nullptr;
        }
        
        last = &new_node;
    }
    
    ~Forward_list() {
        ;
    }

};

template <class T>
class queue {
    using Container_t = Forward_list<T>;
    using iterator = typename Container_t::iterator;
    
    Forward_list() noexcept {
        before_start.emplace_store(&end);
        end.emplace_store();
    }
    
    Forward_list(const Forward_list&) = delete;
    Forward_list(Forward_list &&other) = delete;
    
    std::optional<T> pop_front() noexcept {
        ;
    }
    
    ~Forward_list() {
        ;
    std::atomic_uintmax_t producers_v;
    Container_t data;
    
public:
    queue() noexcept:
        producers_v{0}
    {
        ;
    }
    
    bool has_producers() const noexcept {
        return producers_v.load() != 0;
    }
    
    auto get_producers() const noexcept {
        return producers_v.load();
    }
    
    /**
      * blocking call
      */
    T consume() noexcept {
        auto ret = data.pop_front();
    }
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
