// Problem: CF 2109 E - Binary String Wowee
// https://codeforces.com/contest/2109/problem/E

/*
E. Binary String Wowee
Algorithms/Techniques: Dynamic Programming with Combinatorics, Precomputed Binomial Coefficients

Time Complexity: O(N^3) per test case, where N is the length of the string.
Space Complexity: O(N^2) for the DP table and binomial coefficients.

Problem Summary:
Given a binary string s of length n, perform exactly k operations. Each operation selects an index i such that s[i] = 0,
and flips all characters from index 1 to i inclusive. Count the number of distinct sequences of k operations that result
in a specific final state (the process is defined by choosing indices for flip operations).

Approach:
- Use dynamic programming where f[i][j] represents the number of ways to perform j operations on the first i characters
  of the string.
- For each character in the string, determine how flipping affects previous states and accumulate counts via binomial coefficients.
- Precompute binomial coefficients to optimize calculation of combinations needed during state transitions.

*/

#include <string.h>
#include <iostream>

using namespace std;
constexpr int N = 505, mod = 998244353;
int t, n, m, c[N][N], f[N][N];
char a[N];

// Adds y to x and ensures result is within modulo
inline void add(int &x, int y) { (x += y) >= mod && (x -= mod); }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t, n = 500;
  
  // Precompute binomial coefficients C[i][j] = C(i,j)
  for (int i = 0; i <= n; i++) {
    c[i][0] = 1;
    for (int j = 1; j <= i; j++)
      add(c[i][j] = c[i - 1][j], c[i - 1][j - 1]);
  }
  
  while (t--) {
    cin >> n >> m >> a + 1; // Read input, starting from index 1
    
    memset(f, 0, sizeof(f)); // Reset DP table
    f[0][m] = 1; // Base case: 1 way to do m operations on zero characters

    for (int i = 1; i <= n; i++) {
      a[i] &= 1; // Convert char to int: '0' -> 0, '1' -> 1
      for (int j = 0; j <= m; j++) {
        // For each valid previous state where we have j operations left
        for (int k = j; k <= m; k++) {
          // Add ways to reach current state using transition formula involving binomial coefficient
          add(f[i][j], 1ll * f[i - 1][k] * c[k + 1 - a[i] >> 1][k - j] % mod);
        }
      }
    }
    
    cout << f[n][0] << "\n"; // Output number of ways after processing all characters
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/