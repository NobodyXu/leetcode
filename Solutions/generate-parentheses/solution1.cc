#include <utility>
#include <algorithm>

auto make_leftParenthesis(int n) -> string {
    string s;
    s.reserve(n);
    
    for (int i = 0; i != n; ++n)
        s.push_back('(');
    
    return s;
}

template <class It, class size_type>
void append_rightParenthesis(string &ret, It beg, It end, size_type pos) {
    int left_cnt  = 0;
    int right_cnt = 0;
    
    auto back_inserter = std::back_inserter(ret);
    
    std::copy_n(beg, pos, back_inserter);
    ret.push_back(')');
    std::copy(std::next(beg, pos), end, back_inserter);
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
