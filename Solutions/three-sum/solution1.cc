#include <utility>

#include <algorithm>
#include <vector>
#include <set>

using triplet = vector<int>;
using ref_vector_t = std::vector<typename triplet::const_iterator>;

auto make_ref_vector(const vector<int> &nums) -> ref_vector_t {
    ref_vector_t ret;
    
    ret.reserve(nums.size());
    for (auto it = nums.begin(); it != nums.end(); ++it)
        ret.push_back(it);
    
    std::sort(ref_vector.begin(), ref_vector.end(), [](auto &it1, auto &it2) noexcept {
        return *it1 < *it2;
    });

    return ret;
}

/**
 * @Return x, y, z in ascending order as type triplet
 */
auto sorted(int x, int y, int z) -> triplet {
    auto [s1, s2] = std::minmax(x, y);
    auto s3 = std::max(s2, z);
    
    return {s1, s2, s3};
}

auto threeSum(const ref_vector_t &ref_vector) -> std::set<triplet> {
    std::set<triplet> ret;
    
    for (auto &cit1: ref_vector)
        for (auto &cit2: ref_vector)
            if (it1 != it2) {
                int x = *it1;
                int y = *it2;
                int z = 0 - x - y;
                
                auto ref_it3 = std::lower_bound(ref_vector.begin(), ref_vector.end(), z, 
                                                [](const auto &it, const auto &z) noexcept {
                    return *it < z;
                });
                
                if (ref_it3 != ref_vector.end() && *(*ref_it3) == z && 
                    *ref_it3 != it1 && *ref_it3 != it2)
                    ret.insert(sorted(x, y, z));
            }
    
    return ret;
}

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        auto set = threeSum(make_ref_vector(nums));
        
        vector<triplet> ret;
        ret.reserve(set.size());
        
        for (auto &each: set)
            ret.push_back(std::move(each));
        
        return ret;
    }
};
