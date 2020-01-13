#include <cstdlib>
#include <functional>
#include <iterator>
#include <queue>
#include <type_traits>
#include <utility>

/*
namespace impl {
template <class T>
using rm_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template <class Container>
using value_t = typename Container::value_type;
} /* namespace impl */

/*
template <class Container, 
          class _Container = impl::rm_cvref_t<Container>, 
          class T = impl::value_t<_Container>>
auto make_priority_queue(Container &&c) {
    return std::priority_queue<T, Container>{std::less<T>{}, std::forward<Container>(c)};
}
*/

template <class Queue>
auto pop(Queue &&q) {
    auto top = q.top();
    q.pop();
    return top;
}

template <class RanIt>
class unappendable_priority_queue {
    RanIt beg, end;
    
public:
    using value_type = typename std::iterator_traits<RanIt>::value_type;
    
    template <class Container>
    unappendable_priority_queue(Container &&c) noexcept:
        beg{c.begin()}, end{c.end()}
    {
        std::make_heap(beg, end);
    }
    
    auto& top() const noexcept {
        return *beg;
    }
    
    void pop() noexcept {
        std::pop_heap(beg, end);
        --end;
    }
    
    void modify_top_inplace(value_type &&new_val) noexcept {
        *beg = new_val;
        std::make_heap(beg, end);
    }
    
    auto size() const noexcept {
        return end - beg;
    }
};

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        /*
        auto queue = make_priority_queue(std::move(stones));
        
        while (queue.size() > 1) {
            auto the_first_heaviest = pop(queue);
            auto the_second_heaviest = pop(queue);
            
            if (the_first_heaviest != the_second_heaviest)
                queue.push(std::abs(the_first_heaviest - the_second_heaviest));
        }
        */
        
        auto queue = unappendable_priority_queue<typename vector<int>::iterator>(stones);
        
        while (queue.size() > 1) {
            auto the_first_heaviest = pop(queue);
            auto &the_second_heaviest = queue.top();
            
            if (the_first_heaviest != the_second_heaviest)
                queue.modify_top_inplace(the_first_heaviest - the_second_heaviest);
            else
                queue.pop();
        }
        
        if (queue.size() == 1)
            return queue.top();
        else
            return 0;
    }
};
