// Problem: CF 1858 C - Yet Another Permutation Problem
// https://codeforces.com/contest/1858/problem/C

/*
Code Purpose:
This code solves the problem of constructing a permutation of integers from 1 to n such that the number of distinct GCD values between adjacent elements (with wraparound) is maximized. 

The algorithm works by:
1. Starting with the smallest number in the set.
2. Following a chain where each next number is twice the previous one.
3. Erasing used numbers from the set to avoid reuse.
4. Repeating until all numbers are used.

This greedy approach aims to maximize distinct GCDs by creating a sequence that uses powers of 2, which leads to a small set of distinct GCDs due to the properties of GCD and the structure of the sequence.

Time Complexity: O(n log n) - Each number is inserted and erased once from the set, and set operations (insert, erase, count) take O(log n) time.
Space Complexity: O(n) - Space used by the set to store numbers from 1 to n.

Algorithms/Techniques:
- Greedy algorithm
- Set-based data structure for efficient insertion, deletion, and lookup
- Construction of a sequence based on powers of 2

*/

#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld\n", &n);
    std::set<long> s;
    for (long p = 1; p <= n; p++) {
      s.insert(p);  // Insert all numbers from 1 to n into the set
    }
    while (!s.empty()) {
      long cur = *s.begin();  // Start with the smallest unused number
      while (s.count(cur)) {
        printf("%ld ", cur);  // Print the current number
        s.erase(cur);        // Remove it from the set
        cur *= 2;            // Move to the next number in the sequence (twice the previous)
      }
    }
    puts("");  // Print newline after each permutation
  }
}


// https://github.com/VaHiX/CodeForces/