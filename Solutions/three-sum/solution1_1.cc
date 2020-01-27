#include <utility>
#include <iterator>

#include <algorithm>
#include <vector>
#include <set>

using triplet = vector<int>;

/**
 * @Return x, y, z in ascending order as type triplet
 */
auto sorted(int x, int y, int z) -> triplet {    
    auto [s2, s3] = std::minmax(x, y);
    auto [s4, s5] = std::minmax(s3, z);
    
    auto [s0, s1] = std::minmax(s2, s4);
    
    return {s0, s1, s5};
}

template <class InputIt>
auto skip_same(InputIt beg, InputIt end) {
    auto &val = *beg;
    return std::find_if(std::next(beg), end, [&val](auto &each) noexcept {
        return each != val;
    });
}

auto threeSum_impl(const vector<int> &nums) -> vector<triplet> {
    vector<triplet> ret;
    
    auto end = nums.end();
    for (auto cit1 = nums.begin(); cit1 != end; cit1 = skip_same(cit1, end))
        for (auto cit2 = std::next(cit1); cit2 != nums.end(); cit2 = skip_same(cit2, end)) {
            int x = *cit1;
            int y = *cit2;
            int z = 0 - (x + y);
                
            auto cit3 = std::lower_bound(std::next(cit2), nums.end(), z);
                
            if (cit3 != nums.end() && *cit3 == z)
                ret.push_back(sorted(x, y, z));
        }
    
    return ret;
}

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        return threeSum_impl(nums);
    }
};
