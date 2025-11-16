// Problem: CF 2032 E - Balanced
// https://codeforces.com/contest/2032/problem/E

/*
Purpose: This code solves the problem of making a cyclic array balanced by applying a specific operation.
         The operation increases elements at positions i-1, i, i+1 by 1, 2, 1 respectively, with cyclic wraparound.
         We determine if it's possible to balance the array and, if so, provide a sequence of operations.

Algorithms/Techniques:
- Mathematical analysis of parity and difference in sums
- Simulation with prefix and suffix adjustments
- Greedy approach with backtracking for final correction

Time Complexity: O(n) per test case, where n is the size of the array
Space Complexity: O(n) for storing array and auxiliary arrays
*/

#include <bits/std_abs.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  long long sum = 0;
  // Calculate alternating sum (even indices +, odd indices -) to determine feasibility
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    sum += i % 2 == 0 ? a[i] : -a[i];
  }
  if (n == 1) {
    cout << 0 << '\n';
    return;
  }
  
  // Try different values for the final equal value of the array
  for (int value = 0; value < 4; value++) {
    if (abs(sum) % 2 != value % 2) {
      continue; // Skip incompatible values based on parity
    }
    
    // Initialize answer array and copy of input array
    vector<long long> ans(n), b(n);
    for (int i = 0; i < n; i++) {
      b[i] = a[i];
    }
    
    // Lambda function to update the array based on operation applied at index i
    auto upd = [&](int i) {
      b[i] += ans[i] * 2;
      b[(i + 1) % n] += ans[i];
      b[(i + n - 1) % n] += ans[i];
    };
    
    // Set first operation count and apply to update the array
    ans[0] = (value - sum) / 2;
    upd(0);
    
    // Apply operations for middle elements
    for (int i = 1; i + 1 < n; i++) {
      ans[i] = value - b[i - 1]; // Determine required operations to make this equal to target value
      upd(i);
    }
    
    // Check if final two elements are equal and can form a valid solution
    if (b[n - 2] != b[n - 1] || abs(value - b[n - 1]) % 2) {
      continue;
    }
    
    // Calculate last operations needed and adjust solution
    long long total = (value - b[n - 1]) / 2;
    total *= -1;
    
    // Final adjustment of operations with a correction factor
    for (int i = 0; i < n; i++) {
      long long mem = ans[i];
      ans[i] = i >= n - 2 ? -total : (i % 2 == 0 ? total : -total);
      upd(i);
      ans[i] += mem;
    }
    
    // Verify if the solution is correct
    bool ok = true;
    for (auto &x : b) {
      ok &= x == value;
    }
    
    if (ok) {
      long long val = *std::min_element(ans.begin(), ans.end());
      for (int i = 0; i < n; i++) {
        cout << ans[i] - val << " "; // Output normalized answer
      }
      cout << '\n';
      return;
    }
  }
  
  // If no solution found, return -1
  cout << -1 << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}


// https://github.com/VaHiX/CodeForces/