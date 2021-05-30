#ifndef __UTILS_H__
#define __UTILS_H__

#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

namespace Countdown {
// geneate permutations of size k from list base
std::vector<std::vector<int>> &gen_permutations(std::vector<int> &base, int k);

// geneate tuples of size k from list base
std::vector<std::vector<int>> &gen_tuples(std::vector<int> &base, int k);

// template<class RandIt>
// bool next_k_permutation(RandIt first, RandIt mid, RandIt last) {
//     std::sort(mid, last, std::greater<typename std::iterator_traits<RandIt>::value_type>());
    
//     return std::next_permutation(first, last);
// }

template<class RandIt>
bool next_k_permutation(const RandIt first, const RandIt last, const int k) {
    std::sort(first + k, last, std::greater<typename std::iterator_traits<RandIt>::value_type>());
    
    return std::next_permutation(first, last);
}

template <typename RandIt>
bool next_k_combination(const RandIt first, const RandIt last, const int k) {
    if ((first == last) || (first == first + k) || (last == first + k))
        return false;
    
    RandIt itr1 = first;
    RandIt itr2 = last;
    
    ++itr1;
    if (last == itr1) return false;
    
    itr1 = last;
    --itr1;
    itr1 = first + k;
    --itr2;
    
    while (first != itr1) {
        if (*--itr1 < *itr2) {
            RandIt j = first + k;
            while (!(*itr1 < *j)) ++j;
            
            std::iter_swap(itr1, j);
            ++itr1;
            ++j;
            itr2 = first + k;
            std::rotate(itr1, j, last);
            
            while (last != j) {
                ++j;
                ++itr2;
            }
            
            std::rotate(first + k, itr2, last);
            
            return true;
        }
    }
    
    std::rotate(first, first + k, last);
    
    return false;
}
}

#endif
