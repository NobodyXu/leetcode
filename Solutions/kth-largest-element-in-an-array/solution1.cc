// a O(n log k) solution

#include <cstddef>
#include <utility>
#include <iterator>
#include <functional>

/**
 * ArrayHeap will always place the element which compared less than or equal to
 * any other elements
 */
template <class It, class Comparer>
class ArrayHeap {
    It start;
    std::size_t size;
    Comparer comp;
    
    static auto get_children(std::size_t i) noexcept -> std::pair<std::size_t, std::size_t>
    {
        auto left = (i << 1) + 1;
        return {left, left + 1};
    }
    
    auto min(std::size_t x, std::size_t y) const noexcept
    {
        if (comp(start[y], start[x]))
            return y;
        else
            return x;
    }
    
    void sink(std::size_t i) noexcept
    {
        for (; ;) {
            auto [left, right] = get_children(i);
            
            if (left >= size)
                return;
            else if (right >= size) {
                std::swap(start[i], start[min(i, left)]);
                return;
            }
            
            auto smallest = min(min(i, left), right);
            std::swap(start[i], start[smallest]);
            
            if (i == smallest)
                break;
            i = smallest;
        }
    }
    
public:
    ArrayHeap(It beg, std::size_t len, Comparer &&comparer) noexcept:
        start{beg},
        size{len},
        comp{std::forward<Comparer>(comparer)}
    {
        for (auto i = size; i != 0; )
            sink(--i);
    }
    
    auto& top() const noexcept
    {
        return *start;
    }
    
    template <class U>
    void replace_top(U &&obj) noexcept
    {
        *start = std::forward<U>(obj);
        sink(0);
    }
};

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k)
    {
        ArrayHeap heap{nums.begin(), static_cast<std::size_t>(k), std::less{}};
        
        for (auto it = nums.begin() + k; it != nums.end(); ++it)
            if (heap.top() < *it)
                heap.replace_top(*it);
        
        return heap.top();
    }
};
