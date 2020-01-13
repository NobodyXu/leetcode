#include <cmath>
#include <array>

class Solution {
    // The follwoing function is adapted from
    //https://www.geeksforgeeks.org/number-of-leading-zeros-in-binary-representation-of-a-given-number/
    static char cnt_leading_zeros(int x) {
        // Since the algo below cannot produce right ouput for 
        // x == 0, it is made a special case.
        if (x == 0)
            return 32;
        
        // offsets[] = {16, 8, 4, 2, 1}
        
        // Assume all 32 bits are zero
        char n = 32, offset = n >> 1;
        do {
            if ((x >> offset) != 0) {
                n -= offset;
                x >>= offset;
            }
            
            offset >>= 1;
        } while (offset != 0);        

        // No matter in the last loop, whether the if branch is executed, 
        // the left-most 1 is ignored and is not counted, so returned n - 1.
        return n - 1;
    }
    
    static char cnt_non_lzs(int x) noexcept
    {
        return 32 - cnt_leading_zeros(x);
    }
    
    static constexpr int ceil(double d) noexcept
    {
        return static_cast<int>(std::ceil(d));
    }
    
    /*
    static constexpr const auto log2_10 = 0.3010299957;
    static int estimated_ratio(int x) noexcept
    {
        return 2 << ceil(log2_10 * cnt_non_lzs(x));
    }
    */
    
    // The follwoing function is adapted from
    //https://www.geeksforgeeks.org/number-of-leading-zeros-in-binary-representation-of-a-given-number/
    static int largest_ratio(int x) noexcept
    {
        int ratio = 1;
        int tmp;
        
        tmp = x / 100000; if (tmp != 0) { ratio *= 100000; x = tmp; }
        tmp = x / 100;  if (tmp != 0) { ratio *= 100; x = tmp; }
        tmp = x / 10;   if (tmp != 0) { ratio *= 10; x = tmp;
        tmp = x / 10;   if (tmp != 0) { ratio *= 10; x = tmp; } }
        
        return ratio;
    }
    
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;
        
        auto first = 1;
        auto last = largest_ratio(x);
        while (first < last) {
            if ((x / first % 10) != (x / last % 10))
                return false;
            first *= 10, last /= 10;
        }
        
        return true;
    }
};
