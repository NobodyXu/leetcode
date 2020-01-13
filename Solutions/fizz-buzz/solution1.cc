#include <string>

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> ret;
        ret.reserve(n);
        
        for (int i = 1; i <= n; ++i) {
            switch (unsigned{i % 3 == 0} << 1 | unsigned{i % 5 == 0}) {
                case 0: // i % 3 == 0, i % 5 == 0
                    ret.emplace_back(std::to_string(i));
                    break;
                case 1: // i % 3 == 0, i % 5 != 0
                    ret.emplace_back("Buzz");
                    break;
                case 2: // i % 3 != 0, i % 5 == 0
                    ret.emplace_back("Fizz");
                    break;
                case 3:
                    ret.emplace_back("FizzBuzz");
            }
        }
        
        return ret;
    }
};
