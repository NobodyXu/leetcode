#include <utility>

#include <algorithm>
#include <vector>
#include <set>

using triplet = vector<int>;

auto& sorted(vector<int> &nums) {
    return nums;
}

/**
 * @Return x, y, z in ascending order as type triplet
 */
auto sorted(int x, int y, int z) -> triplet {
    /*
    triplet ret;
    
    ret.reserve(3);
    ret.push_back(x);
    ret.push_back(y);
    ret.push_back(z);
    */
    
    auto [s2, s3] = std::minmax(x, y);
    auto [s4, s5] = std::minmax(s3, z);
    
    auto [s0, s1] = std::minmax(s2, s4);
    
    return {s0, s1, s5};
}

auto threeSum_set(const vector<int> &nums) -> std::set<triplet> {
    std::set<triplet> ret;
    
    for (auto cit1 = nums.begin(); cit1 != nums.end(); ++cit1)
        for (auto cit2 = cit1; ++cit2 != nums.end(); ) {
            int x = *cit1;
            int y = *cit2;
            int z = 0 - (x + y);
                
            auto cit3 = std::lower_bound(nums.begin(), nums.end(), z);
                
            if (cit3 != nums.end() && *cit3 == z && 
                cit3 != cit1 && cit3 != cit2)
                ret.insert(sorted(x, y, z));
        }
    
    return ret;
}

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        auto set = threeSum_set(nums);
        
        vector<triplet> ret;
        ret.reserve(set.size());
        
        for (auto &each: set)
            ret.push_back(std::move(each));
        
        return ret;
    }
};
