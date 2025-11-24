// Problem: CF 2048 I2 - Kevin and Puzzle (Hard Version)
// https://codeforces.com/contest/2048/problem/I2

/*
I2. Kevin and Puzzle (Hard Version)
Algorithm: Dynamic Programming with Segment Processing
Time Complexity: O(n^2) per test case in worst case, but optimized to O(n) amortized in practice
Space Complexity: O(n)

This is the hard version of the problem. You are given a string s of length n consisting of letters L and R only.
You need to count the number of good arrays a such that:
- If s[i] == 'L', then c(1, i-1) = a[i], where c(l,r) is the number of distinct elements from index l to r.
- If s[i] == 'R', then c(i+1, n) = a[i].

The solution uses a combination of preprocessing and dynamic processing:
1. First trim leading L's and trailing R's and process inner part.
2. For each segment determined by valid L/R positions, track how elements contribute to distinct counts.
3. Use bitset and vector-based data structures for efficient computation.

This implementation optimizes the count of good arrays using efficient interval handling and tracking of distinct values with bitsets.
*/

#include <algorithm>
#include <bitset>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define fastcin                                                                \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);
const int N = 2e5 + 5;
using bs = bitset<N>;
int main() {
  fastcin;
  int t, n;
  string s;
  cin >> t;
  while (t--) {
    cin >> n >> s;
    int l = 0;
    bool valid = true;
    // Skip initial L's and final R's that don't affect the core logic
    while (l < n - 1 - l && (s[l] != 'R' || s[n - 1 - l] != 'L'))
      l++;
    if (l >= n - 1 - l) { // All characters are either L or R at the start/end
      cout << "1\n";
      continue;
    }
    // Check if all prefix and suffix segments are consistent for validity
    for (int i = 0; i < l; i++)
      if (s[i] != 'L' || s[n - 1 - i] != 'R')
        valid = false;
    if (!valid) {
      cout << "0\n";
      continue;
    }
    // Extract the middle part to simplify further processing
    s = string(s.begin() + l, s.end() - l);
    int m = s.size(), a = 0;
    vector<int> nl(m, m), nr(m, m), pl(m, -1), pr(m, -1);
    // Preprocess L and R positions from right to left
    for (int i = m - 1; ~i; i--)
      nl[i] = s[i] == 'L' ? i : (i + 1 < m ? nl[i + 1] : m),
      nr[i] = s[i] == 'R' ? i : (i + 1 < m ? nr[i + 1] : m);
    // Preprocess L and R positions from left to right
    for (int i = 0; i < m; i++)
      pl[i] = s[i] == 'L' ? i : (i ? pl[i - 1] : -1),
      pr[i] = s[i] == 'R' ? i : (i ? pr[i - 1] : -1);
    vector<vector<int>> q(m);
    // Build intervals for each L/R interaction
    for (int x = -1, y = m; x < y; x = nl[x + 1], y = pr[y - 1], a++) {
      for (int i = nr[x + 1]; i < nl[x + 1] && i <= pr[y - 1]; i = nr[i + 1])
        q[pr[y - 1]].push_back(i);
      for (int i = pl[y - 1]; i > pr[y - 1] && i >= nl[x + 1]; i = pl[i - 1])
        q[i].push_back(nl[x + 1]);
    }
    bs r, b;
    // Iterate over elements to compute final result using bitset operations
    for (int i = 0; i < m - 1; i++) {
      if (s[i] == 'R')
        r[i] = 1;
      else
        b |= r;
      for (int j : q[i])
        if (j && !b[j])
          a++;
      b >>= 1;
    }
    cout << a << '\n';
  }
}


// https://github.com/VaHiX/codeForces/