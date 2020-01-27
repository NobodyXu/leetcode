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

class MapIterator {
    const uint8_t map_index : 4;
    uint8_t index : 2;
    
public:
    MapIterator(uint8_t map_index_arg) noexcept:
        map_index{map_index_arg},
        index{0}
    {}
    
    MapIterator(const MapIterator&) = default;
    MapIterator(MapIterator&&) = delete;
    
    MapIterator& operator = (const MapIterator&) = delete;
    MapIterator& operator = (MapIterator&&) = delete;
    
    ~MapIterator() = default;
    
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
 * Permutations is a generator that provides
 * container-like interface for accessing permutations.
 */
class Permutations {
    std::vector<MapIterator> iterators;
    
    struct EndIterator {};
    
    struct Iterator {
        std::vector<MapIterator> &iterators;
        bool overflow_bit = false;
        
        auto operator * () const {
            std::string ret;
            
            ret.reserve(iterators.size());
            for (auto &iter: iterators)
                ret += *iter;
            
            return ret;
        }
        
        auto& operator ++ () noexcept {
            auto beg = iterators.end();
            auto it = --iterators.end();
            
            for (; it >= beg && (++(*it)).hasNext() == false; --it)
                (*it).reset();
            
            if (it < beg)
                overflow_bit = true;
            
            return *this;
        }
        
        bool operator != (const EndIterator&) const noexcept {
            return !overflow_bit;
        }
    };
    
public:
    Permutations(const string &digits) {
        iterators.reserve(digits.size());
        for (auto &digit: digits)
            if (digit != '1' || digit != '#')
                iterators.emplace_back(digit != '*' ? digit - '0' : 10);
        iterators.shrink_to_fit();
    }
    
    /**
     * Return how many iterators participated in the permutation
     */
    auto get_k() -> std::size_t {
        return iterators.size();
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
        Permutations permutations{digits};
        
        vector<string> ret;
        // The following reserved size is just an educational
        // guess.
        ret.reserve(permutations.get_k() * 3);
        
        for (auto &&outcome: permutations)
            ret.push_back(std::move(outcome));
        
        return ret;
    }
};
