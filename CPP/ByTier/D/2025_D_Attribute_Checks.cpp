// Problem: CF 2025 D - Attribute Checks
// https://codeforces.com/contest/2025/problem/D

/*
D. Attribute Checks
Algorithms/Techniques: Difference array technique, prefix sums, greedy approach with precomputed states.

Time Complexity: O(n + m)
Space Complexity: O(m)

The problem involves maximizing the number of successful attribute checks by optimally distributing m points
among two attributes (Strength and Intelligence). We use a difference array to track changes in point allocation,
and process events in order, maintaining prefix sums to determine optimal decisions at each step.

*/

#include <algorithm>
#include <iostream>

using namespace std;
int n, m, sum;
int c[2000001], f[2000001]; // c: difference array for point allocation, f: max checks up to current index
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int j = 1; j <= n; j++) {
    int x;
    cin >> x;
    if (x > 0 && sum >= x)
      c[x]++, c[sum + 1]--; // Increment at position x, decrement after sum+1
    if (x < 0 && sum >= -x)
      c[0]++, c[sum + x + 1]--; // Same logic for negative checks
    if (x == 0) { // Point acquisition event
      sum++; // Increment the number of allocated points
      for (int i = 0; i <= sum; i++) {
        if (i != 0)
          c[i] += c[i - 1]; // Compute prefix sum to get actual values in difference array
        f[i] += c[i]; // Accumulate point counts into f array
      }
      for (int i = sum; i >= 1; i--)
        f[i] = max(f[i], f[i - 1]); // Propagate maximum check count forward
      for (int i = 0; i <= sum; i++)
        c[i] = 0; // Reset difference array for next batch of events
    }
  }
  for (int i = 0; i <= sum; i++) {
    if (i != 0)
      c[i] += c[i - 1]; // Compute prefix sum again for final update
    if (i == 0)
      f[i] += c[i]; // Base case of no prior checks
    else
      f[i] = max(f[i - 1], f[i] + c[i]); // Dynamic update based on previous results
  }
  cout << f[sum] << "\n"; // Output the maximum possible successful checks
}


// https://github.com/VaHiX/codeForces/