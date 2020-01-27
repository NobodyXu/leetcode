#include <cstdint>
#include <cassert>
#include <utility>

#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using triplet = vector<int>;
using dict_t = std::unordered_map<int, unsigned>;

struct triplet_hash {
    auto operator () (const vector<int> &vec) const noexcept -> std::size_t {
        // The content of the function are copied from:
        //
        //     https://stackoverflow.com/a/27216842/8375400
        
        std::size_t seed = vec.size();
        for (int i: vec)
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        
        return seed;
    }
};

auto to_dict(const vector<int> &nums) -> dict_t {
    dict_t dict;
    
    dict.reserve(nums.size());
    for (int each: nums)
        ++dict[each];
    
     return dict;
}

/**
 * @Return x, y, z in ascending order as type triplet
 */
auto sorted(int x, int y, int z) -> triplet {    
    auto [s2, s3] = std::minmax(x, y);
    auto [s4, s5] = std::minmax(s3, z);
    
    auto [s0, s1] = std::minmax(s2, s4);
    
    return {s0, s1, s5};
}

auto threeSum_impl(const dict_t &dict) {
    std::unordered_set<triplet, triplet_hash> ret;
    
    auto end = dict.end();
    for (auto cit1 = dict.begin(); cit1 != end; ++cit1) {
        auto cit2 = cit1;
        
        if (cit1->second == 1)
            ++cit2;
        
        for (; cit2 != end; ++cit2) {
            int x = cit1->first;
            int y = cit2->first;
            int z = 0 - (x + y);
                
            auto cit3 = dict.find(z);
                
            if (cit3 != end) {
                switch (uint8_t{cit3 != cit2} << 2 |
                        uint8_t{cit3 != cit1} << 1 | 
                        uint8_t{cit2 != cit1}) {
                    case 0:
                        if (cit1->second < 3)
                            continue;
                        else
                            break;
                        
                    case 2:
                    case 4:
                        assert(false);
                        
                    case 1:
                    case 3:
                        if (cit2->second == 1)
                            continue;
                        
                    case 5:
                    case 6:
                        if (cit1->second == 1)
                            continue;
                        
                    case 7:
                        ;
                }
                
                ret.insert(sorted(x, y, z));
            }
        }
    }
    
    return ret;
}

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        auto set = threeSum_impl(to_dict(nums));
        
        vector<triplet> ret;
        ret.reserve(set.size());
        
        for (auto &each: set)
            ret.push_back(std::move(each));
        
        return ret;
    }
};
