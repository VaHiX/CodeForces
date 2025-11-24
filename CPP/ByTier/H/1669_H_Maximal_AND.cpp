// Problem: CF 1669 H - Maximal AND
// https://codeforces.com/contest/1669/problem/H

/*
H. Maximal AND
Algorithms/Techniques: Greedy, Bit Manipulation

Time Complexity: O(31 * n) per test case, where n is the size of the array.
Space Complexity: O(31) = O(1), since we use a fixed-size vector of 31 elements.

The approach uses a greedy strategy to maximize the bitwise AND:
- For each bit position from most significant to least significant,
  we determine if it's possible to set that bit to 1 in the final result.
- To do so, we count how many numbers already have that bit set.
- If we can afford to set enough bits to make this bit contribute to the AND result,
  we update our result and reduce the number of operations accordingly.

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> v(31); // v[b] stores count of numbers with bit b set
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      for (long b = 0; b < 31; b++) { // Loop through all bits from 0 to 30
        v[b] += (x % 2); // Count how many numbers have bit b set
        x /= 2;
      }
    }
    long res(0);
    for (long b = 30; b >= 0; b--) { // Process bits from most significant to least
      if (v[b] + k >= n) { // If we can make this bit 1 in all elements
        res += (1 << b); // Set this bit in result
        k -= (n - v[b]); // Reduce k by number of operations needed
      }
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/