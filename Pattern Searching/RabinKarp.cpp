#include <iostream>
#include <vector>

#include "RabinKarp.hpp"

std::vector<int> KARP (const std::string& str, const std::string& text) {
    typedef long long LL;
    const LL A = 256;
    const LL B = 101;
    
    std::vector<int> ans;

    LL highestPow = 1;
    const int strSize = str.size();
    const int textSize = text.size();

    LL strHash = 0;
    LL textHash = 0;

    for (int i = 1; i < strSize; i++)
        highestPow = (highestPow * A) % B;
    
    if (strSize > textSize)
        return ans;

    for (int i = 0; i < strSize; i++) {
        strHash = (strHash * A + str[i]) % B;
        textHash = (textHash * A + text[i]) % B;
    }

    for (int i = 0; i <= textSize - strSize; i++) {
        if (strHash == textHash) {
            bool flag = 1;
            for (int j = 0; j < strSize; j++)
                if (str[j] != text[i + j]) {
                    flag = 0;
                    break;
                }
            if (flag)
                ans.push_back(i);

        }
        if (i < textSize - strSize)
            textHash = ((A * (textHash - text[i] * highestPow) + text[i + strSize]) % B + B) % B;
    }
    return ans;
}