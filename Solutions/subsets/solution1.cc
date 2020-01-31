#include <utility>
#include <iterator>
#include <vector>

using PowerSet = vector<vector<int>>;
using size_type = typename vector<int>::size_type;
using const_Iterator = typename vector<int>::const_iterator;

template <class T>
auto next_binomial(T n, T i, T prev_binomial) -> T {
    // The following algorithm is taken from subsection [Multiplicative formula] from
    // section [Computing the value of binomial coefficients] of 
    //     
    //     https://en.wikipedia.org/wiki/Binomial_coefficient
    if (i ==  0 || i == n)
        return 1;
    else if (i == 1)
        return n;
    else
        return prev_binomial + (n + 1 - i) / i;
}

/**
 * Precondition: 1 < i < nums.size()
 */
void takes_subset_impl(PowerSet &powerSet, const vector<int> &nums, size_type i) {
    std::vector<const_Iterator> cits;
    cits.reserve(i);
    cits.push_back(nums.begin());
        
    while (true) {
        while (cits.size() < i)
            cits.push_back(cits.back() + 1);
        
        do {
            vector<int> subset;
            subset.reserve(i);
            
            for (auto cit: cits)
                subset.push_back(*cit);
            
            powerSet.push_back(std::move(subset));
        } while (++cits.back() != nums.end());
        
        // Increment
        size_type len = 0;
        
        do {
            cits.pop_back();
            
            if (cits.empty())
                return;
            
            ++cits.back();            
        } while (std::distance(cits.back(), nums.end()) <= ++len);
    }
}

/**
 * Precondition: 0 <= i < nums.size()
 */
void takes_subset(PowerSet &powerSet, const vector<int> &nums, size_type i) {
    if (i == 1)
        for (int each: nums)
            powerSet.push_back(vector<int>{each});
    else if (i == 0)
        powerSet.emplace_back();
    else
        return takes_subset_impl(powerSet, nums, i);
}

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        PowerSet powerSet;
        
        auto n = nums.size();
        size_type i = 0;
        size_type binomial = 0;
        
        while (i < n) {
            binomial = next_binomial(n, i, binomial);
            powerSet.reserve(powerSet.size() + binomial);
            
            takes_subset(powerSet, nums, i++);
        }
        
        powerSet.reserve(powerSet.size() + 1);
        powerSet.emplace_back(std::move(nums));
        
        return powerSet;
    }
};
