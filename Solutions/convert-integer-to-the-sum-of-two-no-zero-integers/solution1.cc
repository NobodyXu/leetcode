/*
 * Precondition: x is positive
 */
bool is_non_zero_integer(int x) {
    for (uint8_t i = 0; i != 10 && x != 0; ++i, x /= 10)
        if (x % 10 == 0)
            return false;
    
    return true;
}

vector<int> brute_force_getNoZeroIntegers(int n) {
    vector<int> result;
    result.reserve(2);
    
    for (int i = 1; i != n; ++i) {
        if (is_non_zero_integer(i) && is_non_zero_integer(n - i)) {
            result.push_back(i);
            result.push_back(n - i);
            
            return result;
        }
    }
    
    // Shouldn't reach here
    return result;
}

class Solution {
public:
    vector<int> getNoZeroIntegers(int n) {
        return brute_force_getNoZeroIntegers(n);
    }
};
