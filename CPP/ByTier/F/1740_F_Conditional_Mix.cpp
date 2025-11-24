// Problem: CF 1740 F - Conditional Mix
// https://codeforces.com/contest/1740/problem/F

/*
 * Problem: F. Conditional Mix
 * 
 * Purpose: This code calculates the number of distinct multisets of set sizes 
 *          that can be formed by merging elements from an array using specific operations.
 * 
 * Algorithm: 
 *   - The problem reduces to finding the number of ways to partition the frequencies 
 *     of unique values into subsets such that the total sum of subset sizes equals n.
 *   - Dynamic Programming approach using dp[i][j] = number of ways to form multisets 
 *     with i distinct values and total size j.
 * 
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 * 
 * Techniques:
 *   - Dynamic Programming with inclusion-exclusion like logic
 *   - Frequency counting of elements
 *   - Nested loops with optimized iteration bounds
 */

#include <iostream>

typedef long long ll;
enum { N = 2013, mod = 998244353 };
ll a[N], t[N], c[N], n, dp[N][N], r;
int main() {
  std::cin >> n;
  dp[0][0] = 1; // Base case: 0 elements, 0 sum -> 1 way
  for (int i = 1, x; i <= n; i++)
    std::cin >> x, t[++c[x]]++; // Count frequency of each element
  for (int i = 1; i <= n; i++)
    t[i] += t[i - 1]; // Prefix sum of counts
  
  // DP transition: for each value v, update dp[j][k] from dp[j-1][k-v]
  for (int v = n; v; v--)
    for (int j = 1; j * v <= n; j++)
      for (int k = v * j; k <= t[j]; k++)
        (dp[j][k] += dp[j - 1][k - v]) %= mod;
  
  // Sum up all valid multisets of size n
  for (int i = 1; i <= n; i++)
    (r += dp[i][n]) %= mod;
  
  std::cout << r << '\n';
}


// https://github.com/VaHiX/CodeForces/