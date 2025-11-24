// Problem: CF 1706 D1 - Chopping Carrots (Easy Version)
// https://codeforces.com/contest/1706/problem/D1

/*
 * Problem: D1. Chopping Carrots (Easy Version)
 * 
 * Algorithms/Techniques: Brute Force with Optimization
 * 
 * Time Complexity: O(a[0] * n) per test case, where a[0] is the largest element in the array
 * Space Complexity: O(n) for storing the array a
 * 
 * The solution iterates through all possible values of the minimum floor(a[i]/p[i]) 
 * and computes the corresponding maximum floor(a[i]/p[i]) for each valid assignment 
 * of p[i] such that 1 <= p[i] <= k, minimizing the cost.
 */

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 3005;
int n, m;
int k;
int a[N];
int t;
int main() {
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    int ans = 1e9;
    // Iterate through all possible minimum values of floor(a[i]/p[i])
    for (int v = 1; v <= a[0]; v++) {
      int cm = v; // cm stores the maximum floor(a[i]/p[i]) for current v
      for (int i = 0; i < n; i++) {
        // Choose p[i] as the largest possible value (min(k, a[i]/v)) to minimize floor(a[i]/p[i])
        int p = min(k, a[i] / v);
        cm = max(cm, a[i] / p); // Update maximum floor(a[i]/p[i])
      }
      ans = min(ans, cm - v); // Update global minimum cost
    }
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/