#ifndef __UTILS_H__
#define __UTILS_H__

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

namespace Countdown {
template<class RandIt>
bool next_k_permutation(const RandIt first, const RandIt last, const int k) {
    std::sort(first + k, last, std::greater<typename std::iterator_traits<RandIt>::value_type>());
    
    return std::next_permutation(first, last);
}

class Generator {
private:
    const std::vector<char> alph;
    size_t j; // current index of the alph
    size_t i; // current index of word
    std::vector<char> curr_word;
    std::vector<size_t> word_hash;
public:
    Generator(const std::vector<char> &alph, size_t k);
    Generator(std::vector<char> &&alph, size_t k);
    
    bool next_word();

    const std::vector<char> &get_word() const;
};

template<typename T>
void vector_print(const std::vector<T> &v, int k) {
    for (int i = 0; i < k; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}
}

#endif
