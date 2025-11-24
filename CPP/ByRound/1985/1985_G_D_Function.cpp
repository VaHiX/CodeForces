// Problem: CF 1985 G - D-Function
// https://codeforces.com/contest/1985/problem/G

/*
 * Problem: G. D-Function
 * 
 * Purpose:
 * Calculates the number of integers n in the range [10^l, 10^r) that satisfy the condition
 * D(k * n) = k * D(n), where D(n) is the sum of digits of n.
 * 
 * Algorithm:
 * - The key insight is that for the equation D(k * n) = k * D(n) to hold,
 *   the multiplication by k must not cause any carry in digit arithmetic.
 * - This happens when all digits of n are less than or equal to 9/k.
 * - For a number with d digits, there are (1 + 9/k)^d valid combinations (since first digit
 *   can be 1 to 9/k, and others 0 to 9/k).
 * - We compute this using prefix sums based on number of digits.
 * 
 * Time Complexity: O(log(r)) per test case (due to modular exponentiation)
 * Space Complexity: O(1) (constant space used)
 */

#include <stddef.h>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 2e5 + 5, M = 1e6 + 6, mod = 1e9 + 7;

// Fast multiplication modulo
int mul(ll a, int b) { return ((a % mod) * (b % mod)) % mod; }

// Fast addition modulo
int add(ll a, int b) { return (a + b + mod + mod) % mod; }

// Fast exponentiation
int power(int x, int p) {
  int ret = 1;
  while (p) {
    if (p & 1) {
      ret = mul(ret, x);
    }
    x = mul(x, x);
    p /= 2;
  }
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int tt = 1;
  cin >> tt;
  while (tt--) {
    int l, r, k;
    cin >> l >> r >> k;
    if (k > 9) {
      cout << "0\n";
      continue;
    }
    // Compute (1 + 9/k)^r - (1 + 9/k)^l and output it modulo 10^9 + 7
    cout << add(power(9 / k + 1, r), -power(9 / k + 1, l)) << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/