// Problem: CF 1712 E1 - LCM Sum (easy version)
// https://codeforces.com/contest/1712/problem/E1

/*
 * Purpose: This code solves the problem of counting triplets (i, j, k) such that
 *          l <= i < j < k <= r and lcm(i, j, k) >= i + j + k.
 *
 * Algorithm:
 * - For each k in the range [l+2, r], we compute how many valid pairs (i, j)
 *   exist such that i < j < k and the condition is violated (i.e., lcm(i, j, k) < i + j + k).
 * - We do this by:
 *   - Counting divisors of k that are >= l.
 *   - For each valid divisor pair, we calculate combinations (C(n, 2)) where n is number of such divisors.
 *   - Additional cases are handled involving specific divisibility conditions (k % 6 == 0, k % 15 == 0).
 * - Finally, the total number of triplets is computed as:
 *   C(r - l + 1, 3) - invalid_triplets.
 *
 * Time Complexity: O(r * sqrt(r)) due to iterating k up to r and factorization of k.
 * Space Complexity: O(1) - only using a few variables.
 */

#include <iostream>

using namespace std;
long long l, r, fac, cnt;
int main() {
  int T;
  cin >> T;
  while (T--) {
    cnt = 0;
    cin >> l >> r;
    for (int k = l + 2; k <= r; ++k) {
      fac = 0;
      for (int i = 1; i * i <= k; ++i) {
        if (k % i == 0) {
          if (i >= l) // if the divisor itself is >= l
            fac++;
          if (k / i != k && i * i != k && k / i >= l) // avoid double counting when i*i = k, and k/i != k
            fac++;
        }
      }
      cnt += fac * (fac - 1) / 2; // add number of invalid pairs (i,j) for current k
      if (k % 6 == 0 && k / 2 >= l) // special case for k divisible by 6
        cnt++;
      if (k % 15 == 0 && k * 2 / 5 >= l) // special case for k divisible by 15
        cnt++;
    }
    cout << (r - l + 1) * (r - l) / 2 * (r - l - 1) / 3 - cnt << endl; // total triplets minus invalid ones
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/