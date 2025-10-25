// Problem: CF 1417 A - Copy-paste
// https://codeforces.com/contest/1417/problem/A

/*
 * Problem: BThero's Copy-Paste Spell
 *
 * Purpose: Given n piles of candies and a maximum allowed pile size k,
 * determine the maximum number of copy-paste operations that can be performed
 * without any pile exceeding k candies.
 *
 * Algorithm:
 * 1. For each test case, find the pile with minimum candies (idx).
 * 2. For every other pile, calculate how many times we can transfer
 *    candies from it to the smallest pile before reaching k.
 * 3. Sum up these transfers for all piles except the smallest one.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array of piles
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> a(n);
    long idx(0); // index of the pile with minimum candies
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      if (a[p] < a[idx]) { // find the smallest pile
        idx = p;
      }
    }
    long long cnt(0); // total number of operations
    for (long p = 0; p < n; p++) {
      if (p == idx) {
        continue; // skip the smallest pile
      }
      // calculate how many times we can copy from this pile to the smallest
      cnt += (k - a[p]) / a[idx];
    }
    printf("%lld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/