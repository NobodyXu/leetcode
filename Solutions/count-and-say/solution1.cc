#include <algorithm>
#include <utility>

class Solution {
public:
    string countAndSay(int n) {
        string curr = "1";
        for (int cnt = 1; cnt != n; ++cnt) {
            string next_s = "";
            
            for (auto it = curr.begin(), end = curr.end(); it != end; ) {
                auto next = std::find_if(it, end, [&](auto &val) noexcept {
                    return val != *it;
                });
                
                (next_s += std::to_string(next - it)).push_back(*it);
                it = next;
            }
            
            curr = std::move(next_s);
        }
        
        return curr;
    }
};
