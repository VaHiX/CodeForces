// Problem: CF 1680 C - Binary String
// https://codeforces.com/contest/1680/problem/C

/*
Algorithm: 
- The problem involves finding the minimum cost of removing characters from a binary string such that the cost is the maximum of:
  1. Number of '0's remaining in the string
  2. Number of '1's removed from the string
- Key insight: For any valid removal, we can think of a prefix and suffix that are removed.
  - The prefix removed has a certain number of '1's.
  - The suffix removed has a certain number of '1's.
  - The remaining '0's contribute to the first part of the cost.
  - The remaining '1's contribute to the second part of the cost.
- To optimize, we compute a prefix sum of '1's: num[i] = number of '1's in s[0..i-1].
- Let total_ones = num[n] (total number of '1's in the string).
- For each possible prefix (i characters removed from start), we determine how many '1's remain from the suffix (which is (n - total_ones) characters long).
- The number of '1's that are removed is num[i] + num[n] - num[i + total_ones].
- We iterate through all valid prefixes and compute the minimal cost.

Time Complexity: O(n) per test case, where n is the length of the string
Space Complexity: O(n) for storing prefix sums
*/
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define N 200005
int n, num[N];
char s[N];
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    cin >> s;
    // Build prefix sum array of '1's
    for (n = 0; s[n]; n++)
      num[n + 1] = num[n] + (s[n] == '1');
    int ans = num[n]; // Initialize with all '1's being removed (worst case)
    // Try all valid prefix lengths
    for (int i = 0; i + num[n] <= n; i++)
      ans = min(ans, num[n] - num[i + num[n]] + num[i]);
    printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/CodeForces/