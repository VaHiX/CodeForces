// Problem: CF 2152 C - Triple Removal
// https://codeforces.com/contest/2152/problem/C

/*
C. Triple Removal
Algorithms/Techniques: Dynamic Programming, Prefix Sums, Sliding Window
Time Complexity: O(n + q) amortized per test case
Space Complexity: O(n)

This problem involves finding the minimum cost to make a binary subarray empty by removing triplets of identical elements.
The key insight is that for a valid solution:
1. The total count of each element must be divisible by 3 (since we remove them in groups of 3)
2. The length of the subarray must also be divisible by 3
3. The cost calculation is based on the minimum distance between indices of identical elements

We precompute:
- Prefix sums for quick range sum queries
- For each position, track the last occurrence of consecutive same elements to determine
  how many operations can be performed optimally
*/

#include <iostream>

using namespace std;
const int N = 2.5e5 + 2; // Maximum possible size of array
int T, n, q, s[N], lst[N]; // s: prefix sums, lst: last occurrence tracking

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
      cin >> s[i]; // Read input array elements
    
    // lst[i] stores the most recent index where a consecutive sequence of same elements started
    for (int i = 2; i <= n; ++i)
      lst[i] = s[i] == s[i - 1] ? i : lst[i - 1];
    
    // Build prefix sum array for fast range sum queries
    for (int i = 2; i <= n; ++i)
      s[i] += s[i - 1];
    
    // Process each query
    for (int l, r; q--;) {
      cin >> l >> r;
      
      // If subarray length or total sum not divisible by 3, impossible to empty
      if ((r - l + 1) % 3 || (s[r] - s[l - 1]) % 3) {
        cout << "-1\n";
        continue;
      }
      
      // Compute minimum operations: length/3 plus correction term for overlapping sequences
      cout << (r - l + 1) / 3 + (lst[r] <= l) << '\n';
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/