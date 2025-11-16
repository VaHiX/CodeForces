// Problem: CF 706 D - Vasiliy's Multiset
// https://codeforces.com/contest/706/problem/D

#include <cstdio>
#include <set>
/*
Purpose: This code handles a dynamic multiset of integers supporting three operations:
         - Add a number (+x)
         - Remove a number (-x)
         - Find maximum XOR of a given number with any number in the set (?x)

Algorithm:
    Uses a multiset to maintain the elements, and for the query operation (?x):
        - Tries to construct the maximum XOR by greedily choosing bits:
          For each bit from the most significant to least significant:
            - Try to set that bit in the result to 1, if possible.
            - Use lower_bound to test if such a number exists in the multiset.
            - If not, we must set that bit to 0.
        - This is a classic trie-based approach in a multiset.

Time Complexity:
    - Insertion (+): O(log n)
    - Deletion (-): O(log n)
    - Query (?): O(30 * log n) = O(log n) since 30 is constant

Space Complexity:
    - O(n) where n is the number of elements in the multiset.

*/
int main() {
  std::multiset<long> ms;
  ms.insert(0);
  long q;
  scanf("%ld\n", &q);
  while (q--) {
    char cmd;
    long x;
    scanf("%c %ld\n", &cmd, &x);
    if (cmd == '+') {
      ms.insert(x);
    } else if (cmd == '-') {
      ms.erase(ms.find(x)); // Erase only one occurrence
    } else {
      long cur = 0;
      for (int p = 30; p >= 0; p--) {
        // Try to set the p-th bit of cur to 1 (as it would maximize XOR)
        cur |= (~x) & (1 << p);
        // Check if there exists an element in the multiset with the same prefix as cur
        std::multiset<long>::iterator it = ms.lower_bound(cur);
        // If it's past the end, or the p-th bit of *it differs from cur, then we must set cur's p-th bit to 0
        if (it == ms.end() || (*it >> p) != (cur >> p)) {
          cur ^= (1 << p);
        }
      }
      printf("%ld\n", cur ^ x); // Final XOR is cur XOR x
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/