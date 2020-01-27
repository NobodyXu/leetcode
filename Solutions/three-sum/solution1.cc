#include <utility>

#include <algorithm>
#include <vector>
#include <set>

using triplet = vector<int>;

auto& sorted(vector<int> &nums) {
    std::sort(nums.begin(), nums.end());
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
    
    for (auto &x: nums)
        for (auto &y: nums)
            if (&x != &y) {
                int z = 0 - (x + y);
                
                auto cit = std::lower_bound(nums.begin(), nums.end(), z);
                
                if (cit != nums.end() && *cit == z && 
                    &(*cit) != &x && &(*cit) != &y)
                    ret.insert(sorted(x, y, z));
            }
    
    return ret;
}

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        auto set = threeSum_set(sorted(nums));
        
        vector<triplet> ret;
        ret.reserve(set.size());
        
        for (auto &each: set)
            ret.push_back(std::move(each));
        
        return ret;
    }
};
