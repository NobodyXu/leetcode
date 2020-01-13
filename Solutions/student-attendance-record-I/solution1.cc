class Solution {
    using val_t = unsigned char;
public:
    bool checkRecord(const string &s) {
        val_t As = 0;
        val_t Ls = 0;
        
        for (auto &each: s) {
            As += val_t{each == 'A'};
            if (As > 1)
                return false;
            
            Ls <<= 1;
            Ls |= val_t{each == 'L'};
            if ((Ls & 7) == 7)
                return false;
        }
        
        return true;
    }
};
