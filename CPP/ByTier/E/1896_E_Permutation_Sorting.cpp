// Problem: CF 1896 E - Permutation Sorting
// https://codeforces.com/contest/1896/problem/E

/*
Purpose: This code solves the permutation sorting problem where indices become "good" when their value equals their position. 
         It simulates the process of rotating non-good indices and determines the first time each index becomes good.

Algorithms/Techniques:
- Binary Indexed Tree (Fenwick Tree) for efficient range queries and updates
- Coordinate compression and sweep line technique
- Simulation with optimized handling of index rotations

Time Complexity: O(n log n) per test case due to Fenwick tree operations and iteration
Space Complexity: O(n) for storing arrays and auxiliary data structures
*/

#include <iostream>

#define lowbit(x) x & (-x) // Macro to compute the lowest bit of x
const int N = 2e6 + 20; // Maximum size allowed for arrays
using namespace std;
int T, n; // T: number of test cases, n: size of permutation
int a[N], l[N], r[N]; // a: input permutation, l/r: coordinate compression arrays
int s[N], ans[N]; // s: BIT (Fenwick Tree), ans: result array

// Query function for BIT: returns sum from 1 to x
int query(int x) {
  int res = 0;
  for (int i = x; i >= 1; i -= lowbit(i))
    res += s[i];
  return res;
}

// Update function for BIT: increment count at position x
void update(int x) {
  for (int i = x; i <= 2 * n; i += lowbit(i))
    s[i]++;
}

// Main solving function for a single test case
void solve(int n) {
  // Initialize left and right boundaries for each index
  for (int i = 1; i <= n; i++) {
    l[i] = i; // left boundary starts with index i
    if (a[i] < i)
      r[i] = a[i] + n, r[i + n] = N; // For elements that are smaller than index
    else
      r[i] = a[i], r[i + n] = a[i] + n; // For elements that are larger or equal
  }
  
  // Process in reverse order to calculate how many elements have been processed
  for (int i = 2 * n; i >= 1; i--) {
    if (i <= n) {
      // Calculate the time when index a[i] becomes good
      ans[a[i]] = r[i] - l[i] - query(r[i]);
    }
    update(r[i]); // Update BIT with current right boundary
  }
  
  // Output results for all indices
  for (int i = 1; i <= n; i++)
    cout << ans[i] << " ";
  cout << endl;
  
  // Reset global arrays for next test case
  for (int i = 1; i <= 2 * n; i++)
    r[i] = l[i] = a[i] = ans[i] = s[i] = 0;
}

int main() {
  ios::sync_with_stdio(false); // Optimize I/O speed
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i]; // Read input permutation
    solve(n); // Solve the current test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/