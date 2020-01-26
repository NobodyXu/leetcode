#include <algorithm>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (auto it = nums.begin(); it != nums.end(); ++it) {
            int x = *it;
            int y = target - x;
            
            auto result = std::find(nums.begin(), nums.end(), y);
            if (result != nums.end() && result != it)
                return {it - nums.begin(), result - nums.begin()};
        }
        
        // Dummy return statements just to suppress the warning.
        return {};
    }
};
