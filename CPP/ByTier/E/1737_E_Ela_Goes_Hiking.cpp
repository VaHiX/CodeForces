// Problem: CF 1737 E - Ela Goes Hiking
// https://codeforces.com/contest/1737/problem/E

/*
 * Problem: Ela Goes Hiking
 * 
 * Purpose: Calculate the probability that each ant in a line survives the cannibalistic ant experiment,
 * where ants move left or right randomly, crash when adjacent and moving in opposite directions,
 * and the heavier ant eats the lighter one.
 * 
 * Algorithm:
 * - Dynamic Programming with suffix sums to determine the number of valid configurations
 *   where the i-th ant survives.
 * - Use modular arithmetic and fast exponentiation for inverse modulo operations.
 * 
 * Time Complexity: O(n) per test case (after preprocessing)
 * Space Complexity: O(n) for arrays f and s
 * 
 * Techniques:
 * - Fast exponentiation for modular inverse
 * - Suffix sum DP approach
 * - Modular arithmetic
 */

#include <algorithm>
#include <iostream>

using namespace std;
typedef long long LL;
const LL mod = 1e9 + 7, inv2 = (mod + 1) / 2; // inv2 is 2^(-1) mod (1e9 + 7)
int n;
LL f[2000000], s[2000000]; // f[i]: number of ways ant i survives; s[i]: suffix sum of f

// Fast modular exponentiation
LL qmi(LL a, LL b) {
  LL ans = 1;
  while (b) {
    if (b & 1)
      ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}

int main() {
  int t, i;
  cin >> t;
  while (t--) {
    cin >> n;
    f[n] = 1, s[n] = 1, s[n + 1] = 0; // Base case initialization
    
    // Dynamic programming from right to left, calculating number of valid configurations
    for (i = n - 1; i >= 1; i--) {
      int l = i + 1, r = min(2 * i - 1, n); // left and right bounds for range query
      f[i] = (s[l] - s[r + 1] + mod) % mod; // calculate difference of suffix sums
      s[i] = (f[i] + s[i + 1]) % mod; // update suffix sum
    }
    
    LL x = qmi(inv2, n - 1); // calculate (1/2)^(n-1) mod (1e9 + 7)
    
    // Output probability for each ant
    for (i = 1; i <= n; i++)
      cout << f[i] * qmi(2, i / 2) % mod * x % mod << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/