#include <utility>
#include <algorithm>

auto make_leftParenthesis(int n) -> string {
    string s;
    s.reserve(n);
    
    for (int i = 0; i != n; ++n)
        s.push_back('(');
    
    return s;
}

/**
 * If the check fails when coping, set string to empty.
 */
template <class It>
void copy_and_check(It beg, It end, string &ret, int &left_cnt, int &right_cnt) {
    for (It it = beg; it != end; ++it) {
        ret.push_back(*beg);
        
        if (*beg == ')') {
            if (++right_cnt > left_cnt) {
                ret.resize(0);
                return;
            }
        } else
            ++left_cnt;
    }
}

/**
 * If the result is invalid ret will be set to empty
 */
template <class It, class size_type>
void append_rightParenthesis(string &ret, It beg, It end, size_type pos) {
    int left_cnt  = 0;
    int right_cnt = 0;
        
    // Since there is no change to [beg, beg + pos), no check is required
    // But counting of left and right parenthesis is necessary.
    copy_and_check(beg, beg + pos, ret, left_cnt, right_cnt);
    if (ret.empty())
        return;
    
    ret.push_back(')');
    ++right_cnt;
    if (right_cnt > left_cnt) {
        ret.resize(0);
        return;
    }
    
    copy_and_check(std::next(beg, pos), end, ret, left_cnt, right_cnt);
}

vector<string> generateParenthesis_impl(int n) {
    using size_type = typename vector<string>::size_type;
    
    vector<string> ret;
    ret.reserve(10);
    
    ret.push_back(make_leftParenthesis(n));
    
    // The process below will requires ret to be size of (2n, n)
    // But the actually algoritm will just be (2n, n) / (n + 1)
    // It must have invalid pairs according to the theory.
    do {
        ret.reserve(ret.size() * (ret.size() + 1));
        
        for (auto it = ret.begin(), end = ret.end(); it != end; ) {
            string result;
            const auto &str = *it;
            
            for (size_type i = 0; i != str.size(); ++i) {
                result.reserve(str.size() + 1);
                
                append_rightParenthesis(result, str.begin(), str.end(), 0);
                
                if (result.size() != 0)
                    ret.push_back(std::move(result));
            }
            
            // Pop out the current
            if (end < ret.end()) {
                ;
            }
        }
    } while (ret.front().size() != (n << 1));
    
    return ret;
}

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if (n == 0)
            return {""};
        else if (n == 1)
            return {"()"};
        else 
            return generateParenthesis_impl(n);
    }
};
