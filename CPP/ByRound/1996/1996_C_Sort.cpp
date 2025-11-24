// Problem: CF 1996 C - Sort
// https://codeforces.com/contest/1996/problem/C

/*
C. Sort
time limit per test5 seconds
memory limit per test256 megabytes

Problem Description:
Given two strings a and b of length n, and q queries, each query asks for the minimum number of operations
to make sorted(a[l..r]) equal to sorted(b[l..r]). In one operation, we can change any character in range [l,r] to any other character.

Algorithms/Techniques:
- Preprocessing with prefix sums for character frequency counting
- For each query, compare character frequencies in the given range between both strings

Time Complexity: O(n * 26 + q * 26) = O(n + q)
Space Complexity: O(n * 26)

*/
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, q;
    std::cin >> n >> q;
    std::string a, b;
    std::cin >> a >> b;
    
    // Precompute prefix sums for string a
    std::vector<std::vector<long>> va(n + 1, std::vector<long>(26, 0));
    for (long p = 0; p < n; p++) {
      for (long u = 0; u < 26; u++) {
        va[p + 1][u] = va[p][u];  // Copy previous counts
      }
      ++va[p + 1][a[p] - 'a'];   // Increment count of current character
    }

    // Precompute prefix sums for string b
    std::vector<std::vector<long>> vb(n + 1, std::vector<long>(26, 0));
    for (long p = 0; p < n; p++) {
      for (long u = 0; u < 26; u++) {
        vb[p + 1][u] = vb[p][u];  // Copy previous counts
      }
      ++vb[p + 1][b[p] - 'a'];   // Increment count of current character
    }

    while (q--) {
      long left, right;
      std::cin >> left >> right;
      long total(0);
      for (long p = 0; p < 26; p++) {
        long ca = va[right][p] - va[left - 1][p];   // Frequency of char p in a[left..right]
        long cb = vb[right][p] - vb[left - 1][p];   // Frequency of char p in b[left..right]
        long diff = cb - ca;
        if (diff < 0) {
          diff = -diff;
        }
        total += diff;
      }
      std::cout << (total / 2) << std::endl;  // Minimum operations needed
    }
  }
}


// https://github.com/VaHiX/codeForces/