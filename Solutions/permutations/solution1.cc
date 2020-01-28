#include <algorithm>

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ret;
        ret.reserve(nums.size() * nums.size());
        
        std::sort(nums.begin(), nums.end());
        
        do {
            ret.push_back(nums);
        } while (std::next_permutation(nums.begin(), nums.end()));
        
        return ret;
    }
};
