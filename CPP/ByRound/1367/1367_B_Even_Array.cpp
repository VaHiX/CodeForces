// Problem: CF 1367 B - Even Array
// https://codeforces.com/contest/1367/problem/B

/*
B. Even Array
Algorithms/Techniques: Greedy, Parity Check

Time Complexity: O(n) per test case
Space Complexity: O(1)

Given an array of non-negative integers, we need to make it "good" where
each element's parity matches the parity of its index. We can swap any two
elements to achieve this. The goal is to find the minimum number of swaps.

Approach:
- For each position i, check if parity of i matches parity of a[i].
- Count mismatches for even indices (i % 2 == 0) and odd indices (i % 2 == 1).
- If counts are equal, the minimum swaps needed is half of either count.
- If not equal, return -1 as it's impossible to balance.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long w(0), v(0); // w: mismatches at even indices, v: mismatches at odd indices
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      if (p % 2 < a % 2) { // parity of index < parity of value => even index with odd value
        ++w;
      } else if (p % 2 > a % 2) { // parity of index > parity of value => odd index with even value
        ++v;
      }
    }
    if (w == v) {
      printf("%ld\n", w); // Minimum swaps = number of mismatches at even indices (or odd)
    } else {
      puts("-1"); // Impossible to make array good
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/