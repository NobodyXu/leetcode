#include <cstddef>
#include <string>

template <class Iterator>
auto find_not(Iterator beg, Iterator end) {
    const auto &value = *beg;
    
    auto it = beg;
    do {
        ++it;
    } while (it != end && *it == value);
    
    return it;
}

/*
 * Simple stream with no end detection
 *
 * Due to the fact that the length must be <= original array.
 */
template <class Iterator>
class Stream {
    Iterator it;
    int length;

public:
    Stream(Iterator beg) noexcept:
        it{beg}
    {}
        
    auto& operator << (char ch) noexcept {
        *it = ch;
        ++it;
        return *this;
    }
    
    auto& operator << (std::ptrdiff_t num) {
        auto str = std::to_string(num);
        
        for (char ch: str) {
            *it = ch;
            ++it;
        }
        
        return *this;
    }
    
    auto get_iterator() const noexcept {
        return it;
    }
};

class Solution {
public:
    int compress(vector<char>& chars) {
        auto in = chars.begin();
        auto end = chars.end();
        
        auto out_stream = Stream(in);
        
        while (in != end) {
            auto next_in = find_not(in, end);
            
            auto diff = next_in - in;
            if (diff > 1)
                out_stream << *in << diff;
            else
                out_stream << *in;
            
            in = next_in;
        }
        
        return out_stream.get_iterator() - chars.begin();
    }
};
