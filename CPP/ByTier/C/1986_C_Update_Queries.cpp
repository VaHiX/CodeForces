// Problem: CF 1986 C - Update Queries
// https://codeforces.com/contest/1986/problem/C

/*
C. Update Queries
Algorithm: Greedy + Sorting
Time Complexity: O(m * log(m) + n + m)
Space Complexity: O(m + n)

The problem asks to find the lexicographically smallest string that can be obtained after m update operations,
given a string s, an array of indices, and a string of characters to replace at those indices.
We are allowed to reorder both the indices array and the characters string to achieve the optimal result.

Approach:
1. For each query:
   - Read the input: string s, indices array ind, and character string c
   - Store all indices in a set (sorted automatically)
   - Sort the characters string c lexicographically
   - Assign the smallest available character from c to the earliest index in the sorted indices set.
   - Output the resulting string.

Key Insights:
- To minimize the lexicographical result, place smaller characters at earlier positions.
- We process the indices in sorted order and assign characters greedily to get the minimal output.
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long t;
  std::cin >> t;
  while (t--) {
    long n, m;
    std::cin >> n >> m;
    std::string s;
    std::cin >> s;
    std::set<long> t; // Store indices in a set to sort them automatically
    for (long p = 0; p < m; p++) {
      long x;
      std::cin >> x;
      t.insert(--x); // Convert to 0-based index and insert
    }
    std::string r;
    std::cin >> r;
    std::sort(r.begin(), r.end()); // Sort characters lexicographically to assign smallest first
    long idx(0);
    for (std::set<long>::iterator it = t.begin(); it != t.end(); it++) {
      long pos = *it;
      s[pos] = r[idx++]; // Assign next smallest character to current index
    }
    std::cout << s << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/