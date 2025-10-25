// Problem: CF 1734 C - Removing Smallest Multiples
// https://codeforces.com/contest/1734/problem/C

/*
C. Removing Smallest Multiples
Algorithm: Sieve-like approach to compute minimum cost of transforming a set S into T.
Time Complexity: O(n log n) per test case, where n is the size of the input string.
Space Complexity: O(n) for storing the string and auxiliary variables.

The problem can be interpreted as:
Given a set S = {1, 2, ..., n} and subset T ⊆ S,
we want to find the minimum cost to delete elements from S such that only elements in T remain.
Each deletion operation chooses k (1 ≤ k ≤ n) and deletes the smallest multiple of k currently in S.
The cost for this operation is k.

Approach:
- Use a modified sieve-like algorithm:
  - Iterate over all potential k values from 1 to n.
  - For each k, find its multiples in the current set.
  - If some multiple is not in T (i.e. should be deleted), we pay cost k for deleting it.
  - Mark visited elements with 'x' to avoid redundant processing.

Key insight:
- Instead of simulating all operations, process numbers in order of their smallest factors.
- This is effectively applying a sieve where we remove numbers not in T, and assign cost based on the factor used.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    // Prepend 'a' to simplify indexing from 1
    s = "a" + s;
    long long cnt(0);
    for (long p = 1; p < s.size(); p++) {
      // Skip if this position is already marked or already in T (i.e. should not be removed)
      if (s[p] == '1') {
        continue;
      }
      // Traverse all multiples of p starting from p and mark them as processed
      for (long q = p; q < s.size() && s[q] != '1'; q += p) {
        // If this multiple is not in T, it needs to be removed; pay cost p
        cnt += p * (s[q] == '0');
        // Mark this position as visited (to prevent reprocessing)
        s[q] = 'x';
      }
    }
    std::cout << cnt << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/