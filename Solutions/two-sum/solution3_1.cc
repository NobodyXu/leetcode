#include <algorithm>

auto make_ref_vector(const vector<int> &nums) -> vector<typename vector<int>::const_iterator> {
    vector<typename vector<int>::const_iterator> ret;
    
    ret.reserve(nums.size());
    for (auto it = nums.begin(); it != nums.end(); ++it)
        ret.push_back(it);
    
    return ret;
}

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        auto ref_vector = make_ref_vector(nums);
        
        std::sort(ref_vector.begin(), ref_vector.end(), [](auto &it1, auto &it2) noexcept {
            return *it1 < *it2;
        });
        
        for (auto it = nums.cbegin(); it != nums.cend(); ++it) {
            int x = *it;
            int y = target - x;
            
            // **result >= y
            auto result = std::lower_bound(ref_vector.cbegin(), ref_vector.cend(), y, [](const auto &it, const auto &y) noexcept {
                    return *it < y;
            });
            if (result != ref_vector.cend() && **result == y && *result != it)
                return {it - nums.cbegin(), *result - nums.cbegin()};
        }
        
        // Dummy return statements just to suppress the warning.
        return {};
    }
};
