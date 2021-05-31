#include "utils.h"

#include <utility>

using namespace std;

namespace Countdown {
Generator::Generator(const vector<char> &alph, size_t k) : alph{alph},
    j{1}, i{k - 1 >= 0 ? k - 1 : 0}, curr_word(k, alph[0]), word_hash(k) { }

Generator::Generator(vector<char> &&alph, size_t k) : alph{move(alph)},
    j{1}, i{k - 1 >= 0 ? k - 1 : 0}, curr_word(k, alph[0]), word_hash(k) { }

const vector<char> &Generator::get_word() const { return curr_word; }

bool Generator::next_word() {
    if (curr_word.empty()) return false;
    
    if (j < alph.size()) {
        curr_word[i] = alph[j++];
        ++word_hash[i];
    } else if (i) {
        while (word_hash[i] == alph.size() - 1) {
            curr_word[i] = alph[0];
            word_hash[i] = 0;
            --i;
        }
        if (i == -1) return false;
        curr_word[i] = alph[++word_hash[i]];
        i = curr_word.size() - 1;
        j = 1;
    } else {
        return false;
    }
    return true;
}
}
