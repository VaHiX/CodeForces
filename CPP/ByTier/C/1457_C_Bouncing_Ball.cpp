// Problem: CF 1457 C - Bouncing Ball
// https://codeforces.com/contest/1457/problem/C

/*
C. Bouncing Ball

Algorithms/Techniques: Dynamic Programming, Sliding Window

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

Problem Description:
We are given a row of n cells, each either has a platform (1) or not (0).
A ball is thrown from the left and must land on platforms at positions p, p+k, p+2k, ..., until it goes out of bounds.
We want to make this path possible with minimum cost where:
- Adding a platform costs x seconds
- Removing the first cell costs y seconds (and decreases n by 1)

Approach:
1. Preprocess the number of missing platforms from position p onwards with step k using DP.
2. For each valid starting position p, calculate cost of making that path work:
   - Cost = (number of missing platforms in the path) * x + (number of cells removed) * y
3. Use sliding window to minimize the total cost.

*/
#include <iostream>
#include <vector>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  long t;
  std::cin >> t;
  while (t--) {
    long n, start, step;
    std::cin >> n >> start >> step;
    --start; // Convert to 0-based indexing
    std::string s;
    std::cin >> s;
    long x, y;
    std::cin >> x >> y;
    std::vector<long> v(n + step, 0); // DP array for counting 0s from position p with step k
    
    // Build the prefix sum-like array from right to left
    // v[p] represents number of '0' characters from position p to the end with step size step
    for (long p = n - 1; p >= 0; p--) {
      v[p] = v[p + step] + (s[p] == '0');
    }
    
    long long ans(2e18); // Initialize result to a large value
    
    // For each valid starting platform position, compute the cost
    for (long p = start; p < n; p++) {
      // Cost = (missing platforms in the bouncing path) * x + (cells removed) * y
      long long cur = x * v[p] + (p - start) * y;
      ans = (ans < cur) ? ans : cur; // Keep minimum cost
    }
    
    std::cout << ans << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/