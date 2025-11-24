// Problem: CF 2048 I1 - Kevin and Puzzle (Easy Version)
// https://codeforces.com/contest/2048/problem/I1

/*
 * Problem: Kevin and Puzzle (Easy Version)
 * 
 * Purpose: 
 *   Given a string of 'L' and 'R' characters, construct a non-negative array such that:
 *   - If s[i] == 'L', then c(1, i-1) must equal a[i] (number of distinct elements from index 1 to i-1)
 *   - If s[i] == 'R', then c(i+1, n) must equal a[i] (number of distinct elements from index i+1 to n)
 * 
 * Approach:
 *   Use a recursive DFS approach that builds the array from both ends, trying to satisfy the constraints.
 *   Key insight: for each valid configuration, we can determine lower bounds for values in the array,
 *   and ensure that the structure is consistent.
 * 
 * Time Complexity: O(n) - Each element is processed once during recursion.
 * Space Complexity: O(n) - For storing the string, array, and recursion stack.
 * 
 * Techniques:
 *   - Recursive DFS with backtracking
 *   - Two-pointer technique from both ends
 *   - Conditional assignment based on 'L' or 'R'
 * 
 * Input:
 *   - Multiple test cases
 *   - Each case has a string of 'L' and 'R' of length n
 * 
 * Output:
 *   - A valid array if possible, else -1
 */

#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

const int MAXN = 2e5 + 5;
int n, a[MAXN], ok; // ok tracks validity of solution
char s[MAXN];

// DFS function to build array from indices l to r
// d: direction flag used for consistency checks
// x: current value to assign to base case
int dfs(int l, int r, int d, int x) {
  if (l > r)
    return 0;
  if (l == r) {
    // Base case: only one element, assign x
    return a[l] = x;
  }
  
  if (s[l] == s[r]) {
    // If both ends are same character
    a[l] = x;
    // Recursively compute inner part and set a[r] to max of (x+1, computed inner) + 1
    a[r] = max(x, dfs(l + 1, r - 1, 1, x + 1)) + 1;
    
    // Swap if needed depending on s[r] (for R case)
    if (s[r] == 'R')
      swap(a[l], a[r]);
    return max(a[l], a[r]);
  }
  
  if (s[l] == 'L') {
    // L case: both a[l] and a[r] set to x
    a[l] = a[r] = x;
    // Continue with inner part, incrementing x
    return max(x, dfs(l + 1, r - 1, d, x + 1));
  }
  
  // R case: invalid if d == 1, otherwise fill entire range with x + 1
  ok &= d != 1;
  fill(a + l, a + r + 1, x + 1);
  return x + 1;
}

void solve() {
  cin >> n, ok = 1;
  for (int i = 1; i <= n; ++i)
    cin >> s[i], a[i] = 0; // Read input and reset array
  dfs(1, n, -1, 0); // Start recursion
  if (!ok)
    cout << "-1\n"; // No valid solution
  else
    for (int i = 1; i <= n; ++i)
      cout << a[i] << " \n"[i == n]; // Print result
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int _;
  cin >> _;
  while (_--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/