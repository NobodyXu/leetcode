#include <cstdint>
#include <cmath>
#include <utility>

#include <vector>

using cstr_t = const char*;

static constexpr cstr_t d2l_map[] = {"abc",  // 2
                                     "def",  // 3
                                     "ghi",  // 4
                                     "jkl",  // 5
                                     "mno",  // 6
                                     "pqrs", // 7
                                     "tuv",  // 8
                                     "wxyz", // 9
                                    };

class MapIterator {
    const uint8_t map_index : 4;
    uint8_t index : 3;
    
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
 * Combinations is a generator that provides
 * container-like interface for accessing permutations.
 */
class Combinations {
    std::vector<MapIterator> iterators;
    
    struct EndIterator {};
    
    class Iterator {
        std::vector<MapIterator> &iterators;
        bool overflow_bit;
        
    public:
        Iterator(std::vector<MapIterator> &iters) noexcept:
            iterators{iters},
            overflow_bit{iters.empty() ? true : false}
        {}
        
        auto operator * () const {
            std::string ret;
            
            ret.reserve(iterators.size());
            for (const auto &iter: iterators)
                ret += *iter;
            
            return ret;
        }
        
        auto& operator ++ () noexcept {
            auto beg = iterators.begin();
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
    Combinations(const string &digits) {
        iterators.reserve(digits.size());
        for (auto &digit: digits)
            iterators.emplace_back(digit - '2');
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
        Combinations combinations{digits};
        
        vector<string> ret;
        // The following reserved size is just an educational
        // guess.
        auto guessed_size = std::size_t{std::pow(3, combinations.get_k())};
        ret.reserve(guessed_size);
        
        for (auto &&outcome: combinations)
            ret.push_back(std::move(outcome));
        
        return ret;
    }
};
