// Problem: CF 1814 B - Long Legs
// https://codeforces.com/contest/1814/problem/B

/*
Purpose: This code solves the "Long Legs" problem where a robot starts at (0,0) with leg length 1 and must reach a target cell (a,b) using minimal moves. Each move can either jump in x or y direction based on current leg length, or increase leg length by 1.

Algorithms/Techniques:
- Mathematical optimization using square root approximation and small offset search
- Greedy approach with binary-like logic to minimize steps

Time Complexity: O(1) per test case (constant number of iterations due to bounded loop)
Space Complexity: O(1) - only using a few variables regardless of input size

*/
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
typedef priority_queue<int, vector<int>, greater<int>> pql;
const int N = 1e5 + 3;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ll t = 1, n, k;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    ll s = sqrt(n + k); // Estimate optimal leg length based on sum of coordinates
    ll ans = 1e15; // Initialize answer to large value
    for (int i = -100; i <= 100; i++) { // Try small adjustments around the estimate
      if (s + i <= 0)
        continue; // Skip non-positive leg lengths
      // Calculate moves needed: one part for x-direction, one for y-direction,
      // plus one step to increase leg length to (s+i)
      ans = min(ans, (s + i - 1 + ll((n + s + i - 1) / (s + i)) +
                      ll((k + s + i - 1) / (s + i))));
    }
    cout << ans << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/