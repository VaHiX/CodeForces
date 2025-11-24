// Problem: CF 2030 D - QED's Favorite Permutation
// https://codeforces.com/contest/2030/problem/D

/*
D. QED's Favorite Permutation

Algorithm/Techniques:
- Key insight: A permutation can be sorted using given operations if and only if for every position i, 
  there exists a valid way to move element i to its correct place. The allowed swaps are:
    - If s[i] = 'L', we can swap p[i] with p[i-1]
    - If s[i] = 'R', we can swap p[i] with p[i+1]
  This implies that the position of the element `i` in the permutation, after considering these
  operations, should allow for a valid sequence of swaps to bring `i` into its correct place.
- The check function evaluates a local constraint: whether it's possible to perform an operation that
  would allow moving elements from left to right (or vice versa), such that some element could end up at index i
  in a sorted array through a valid sequence of moves.

Time Complexity:
- Preprocessing and initial count: O(n)
- Each query: O(1) amortized over all queries due to efficient updates using a counter.
- Total time complexity per test case: O(n + q)

Space Complexity:
- O(n) for the arrays used to track information about elements and operations.
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
const int N = 2e5 + 2;
int T, n, q, p[N], cnt;
bool f[N], b[N];
string s;

// Check if an operation between adjacent positions i-1 and i leads to a valid configuration
bool check(int x) { return !f[x] && !b[x] && b[x + 1]; }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> T; T--;) {
    cin >> n >> q;
    cnt = 0;
    
    // Initialize `f[i]` such that it indicates if all elements from 1 to i are in their correct place
    // (sorted in non-decreasing order starting from 1)
    for (int i = 1, x = 0; i <= n; ++i) {
      cin >> p[i];
      x = max(x, p[i]);
      f[i] = x == i;
    }
    
    // Convert the string s into a boolean array where true means 'R', false means 'L'
    cin >> s;
    for (int i = 0; i < n; ++i)
      b[i + 1] = s[i] == 'R';
      
    // Count valid pairs of adjacent positions where a swap operation could help in making the array sorted
    for (int i = 1; i < n; ++i)
      cnt += check(i);
      
    // Process each query
    for (int i; q--;) {
      cin >> i;
      
      // Remove contribution of old status of this index from the count
      cnt -= check(i - 1) + check(i);
      
      // Toggle the value at index i in the boolean array `b`
      b[i] ^= 1;
      
      // Add contribution of new status of this index to the count
      cnt += check(i - 1) + check(i);
      
      // Output result based on whether there are any invalid configurations
      cout << (cnt ? "NO\n" : "YES\n");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/