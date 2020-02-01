#include <iterator>
#include <algorithm>

auto make_leftParenthesis(int n) -> string {
    string s;
    s.reserve(n);
    
    for (int i = 0; i != n; ++n)
        s.push_back('(');
    
    return s;
}

template <class It, class size_type>
auto append_rightParenthesis(It beg, It end, size_type pos) -> string {
    string ret;
    ret.reserve(std::distance(end, beg) + 1);
    
    auto back_inserter = std::back_inserter(ret);
    
    std::copy_n(beg, pos, back_inserter);
    ret.push_back(')');
    std::copy(std::next(beg, pos), end, back_inserter);
    
    return ret;
}

vector<string> generateParenthesis_impl(int n) {
    using size_type = typename vector<string>::size_type;
    
    vector<string> ret;
    ret.reserve(10);
    
    ret.push_back(make_leftParenthesis(n));
    
    // The process below will requires ret to be size of (2n, n)
    // But the actually algoritm will just be (2n, n) / (n + 1)
    // It must have dups.
    do {
        ret.reserve(ret.size() * (ret.size() + 1));
        
        for (auto &each: ret) {
            do {
                ;
            } while ()
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
