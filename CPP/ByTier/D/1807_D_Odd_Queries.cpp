// Problem: CF 1807 D - Odd Queries
// https://codeforces.com/contest/1807/problem/D

/*
D. Odd Queries
Algorithm: Prefix Sum + Bit Manipulation
Time Complexity: O(n + q) per test case
Space Complexity: O(n) per test case

The problem asks whether changing elements in a range [l, r] to value k will make the total sum of array odd.
Key Insight:
- Only parity (odd/even) matters for the sum.
- We can use prefix sums modulo 2 to quickly compute the effect of a query.
- For range [l, r], if we change all values to k:
  - The change in sum is: (r - l + 1) * (k % 2)
  - So final parity = (original_sum % 2) XOR (change_in_parity)
- To compute this quickly, we precompute prefix sums of the original array modulo 2.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, q;
    scanf("%ld %ld", &n, &q);
    std::vector<long> a(n + 1, 0);  // Prefix sum array modulo 2
    long cs(0);                     // Cumulative sum mod 2
    for (long p = 1; p <= n; p++) {
      long x;
      scanf("%ld", &x);
      cs += x;                      // Add current element to cumulative sum
      cs %= 2;                      // Keep only parity
      a[p] = cs;                    // Store prefix sum mod 2
    }
    while (q--) {
      long l, r, k;
      scanf("%ld %ld %ld", &l, &r, &k);
      long rep = ((r - l + 1) % 2) * (k % 2);  // Number of elements in range * parity of k
      // Final parity calculation using prefix sums
      puts(((2 + cs + rep + a[r] - a[l - 1]) % 2) ? "YES" : "NO");
    }
  }
}


// https://github.com/VaHiX/codeForces/