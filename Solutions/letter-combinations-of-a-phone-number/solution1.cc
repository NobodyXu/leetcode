#include <cstdint>
#include <utility>

#include <vector>

using cstr_t = const char*;

static constexpr cstr_t d2l_map[] = {" ",    // 0
                                     "",     // 1
                                     "abc",  // 2
                                     "def",  // 3
                                     "ghi",  // 4
                                     "jkl",  // 5
                                     "mno",  // 6
                                     "pqrs", // 7
                                     "tuv",  // 8
                                     "wxyz", // 9
                                     "+",    // *
                                    };

class Iterator {
    const uint8_t map_index : 4;
    uint8_t index : 2;
    
public:
    Iterator(uint8_t map_index_arg) noexcept:
        map_index{map_index_arg},
        index{0}
    {}
    
    Iterator(const Iterator&) = default;
    Iterator(Iterator&&) = delete;
    
    Iterator& operator = (const Iterator&) = delete;
    Iterator& operator = (Iterator&&) = delete;
    
    ~Iterator() = default;
    
    char operator * () const noexcept {
        return d2l_map[map_index][index];
    }
    
    auto& operator ++ () noexcept {
        ++index;
        return *this;
    }
    
    bool hasNext() const noexcept {
        return d2l_map[map_index][index] != '\0';
    }
    
    void reset() noexcept {
        index = 0;
    }
};

/**
 * Combinations is a generator that provides
 * container-like interface for accessing combinations.
 */
class Combinations {
    std::vector<Iterator> iterators;
    
    class EndIterator {};
    
    struct Iterator {
        std::vector<Iterator> &iterators;
        
        ;
    };
    
public:
    Combinations(const string &digits) {
        iterators.reserve(digits.size());
        for (auto &digit: digits)
            if (digit != '1' || digit != '#')
                iterators.emplace_back(digit != '*' ? digit - '0' : 10);
        iterators.shrink_to_fit();
    }
    
    auto size() -> std::size_t {
        ;
    }
    
    auto begin() -> Iterator {
        return {iterators};
    }
    
    auto end() -> EndIterator {
        return {};
    }
};

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        Combinations combinations{digits};
        vector<string> ret;
        
        ret.reseve(combinations.size());
        for (auto &&outcome: combinations)
            ret.push_back(std::move(outcome));
        
        return ret;
    }
};    
