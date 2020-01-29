#include <cstdint>
#include <iterator>
#include <string_view>

template <class String_view, 
          class size_type = typename String_view::size_type, 
          class CharT     = typename String_view::value_type>
auto count(String_view str, size_type index, CharT ch) noexcept {
    auto result = str.find_first_not_of(ch, index);
    
    if (result == String_view::npos)
        return 0;
    else
        return result - index;
}

class Regex {
    using string_view = std::basic_string_view<typename string::value_type,
                                               typename string::traits_type>;
    using size_type = typename string_view::size_type;
        
    string_view pat;
    
    /**
     * Precondition: index <= pat.size()
     */
    bool is_wildcard(size_type index) const noexcept {
        return index != pat.size() && pat[index] == '*';
    }
    
    /**
     * Precondition: start < pat.size()
     */
    bool are_wildcards(size_type start) const noexcept {
        do {
            if (start + 1 == pat.size() || pat[start + 1] != '*')
                return false;
            
            start += 2;
        } while (start != pat.size());
        
        return true;
    }
    
public:
    Regex(string_view p) noexcept:
        pat{p}
    {}
    
    bool fullmatch(string_view str) {
        size_type str_index = 0;
        size_type pat_index = 0;
        
        while (true)
            // Check end condition
            switch ((uint8_t{str_index != str.size()} << 1) | uint8_t{pat_index != pat.size()}) {
                case 0:
                    // When both reaches the end
                    return true;
                    
                case 1: // There are unmatched pattern
                    return are_wildcards(pat_index);
                    
                case 2: // There are unmatched str
                    return false;
                    
                case 3:
                    if (is_wildcard(pat_index + 1)) {
                        if (pat[pat_index] == '.') {
                            if (pat_index + 2 == pat.size())
                                return true;
                            
                            ;
                        } else {
                            auto matched_chs = count(str, str_index,     pat[pat_index]);
                            auto min_match   = count(pat, pat_index + 2, pat[pat_index]);
                                        
                            if (matched_chs < min_match)
                                return false;
                        
                            str_index += matched_chs;
                            pat_index += 2 + min_match;
                        }
                    } else if (str[str_index] == pat[pat_index] || pat[pat_index] == '.') {
                        ++str_index;
                        ++pat_index;
                    } else
                        return false;
            }
    }
};

class Solution {
public:
    bool isMatch(string s, string p) {
        return Regex{p}.fullmatch(s);
    }
};
