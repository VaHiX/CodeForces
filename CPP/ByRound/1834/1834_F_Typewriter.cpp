// Problem: CF 1834 F - Typewriter
// https://codeforces.com/contest/1834/problem/F

/*
Problem: F. Typewriter
Algorithm: Difference array technique with lazy propagation for range updates and point queries
Time Complexity: O(n + q) where n is the number of cells and q is the number of queries
Space Complexity: O(n) for storing the difference arrays and auxiliary data structures

This solution uses a difference array technique to efficiently calculate the minimum number of carriage resets needed
to arrange the numbers in their correct positions after each operation. The key insight is that we precompute
the cost for all possible shifts and use a lazy propagation technique to handle the operations.
*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
int n;
vector<vector<int>> ans;

// Function to add a range update to the difference array
void add_range(int i, int j, int z, int x) {
  // If range is valid, update the difference array
  if (i <= j) {
    ans[z][i] += x;
    ans[z][j + 1] -= x;
  } else {
    // Handle wrap-around case by splitting into two ranges
    add_range(i, n - 1, z, x);
    add_range(0, j, z, x);
  }
}

void solve() {
  cin >> n;
  // ans[0] for original array, ans[1] for reversed array
  ans = vector<vector<int>>(2, vector<int>(n + 1));
  vector<int> p(n), pr(n);
  
  // Read input sequence and reverse it for processing
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    pr[n - i - 1] = p[i];
  }
  
  // For each element in the original array, compute the cost to place it correctly
  for (int i = 0; i < n; i++) {
    if (p[i] != n)  // Don't process the last element
      add_range((n - i + p[i]) % n, n - i - 1, 0, 1);
    if (pr[i] != n)  // Don't process the last element in reversed array
      add_range((n - i + pr[i]) % n, n - i - 1, 1, 1);
  }
  
  // Convert difference array to prefix sum array to get actual costs
  for (int i = 1; i <= n; i++)
    ans[0][i] += ans[0][i - 1];
  for (int i = 1; i <= n; i++)
    ans[1][i] += ans[1][i - 1];
    
  // Initial answer for the original array  
  cout << ans[false][0] << "\n";
  
  int q;
  cin >> q;
  int shift = 0;
  bool r = false;
  
  // Process all queries
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      // Left shift: adjust shift amount
      int k;
      cin >> k;
      shift = (shift - k + n) % n;
    } else if (t == 2) {
      // Right shift: adjust shift amount
      int k;
      cin >> k;
      shift = (shift + k) % n;
    } else {
      // Reverse operation: toggle flag and adjust shift
      r = !r;
      shift = (n - shift) % n;
    }
    // Output the cost for current state and shift
    cout << ans[r][shift] << "\n";
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/