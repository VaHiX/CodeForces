// Problem: CF 1294 D - MEX maximizing
// https://codeforces.com/contest/1294/problem/D

/*
D. MEX maximizing
Algorithms/Techniques: Modular arithmetic, greedy approach with frequency counting

Time Complexity: O(q) amortized
Space Complexity: O(x)

The problem asks us to maximize the MEX (minimum excluded value) of an array after each query,
where we can add or subtract x from any element to make it non-negative.
We use a frequency count modulo x to track how many elements exist in each residue class.
The key insight is that we can always "shift" numbers into any valid range by adding/subtracting x,
so the MEX is determined by the minimum missing non-negative integer in the sequence of
frequencies across modular classes.

*/
#include <cstdio>
#include <vector>
int main() {
  long n, x;
  scanf("%ld %ld", &n, &x);
  std::vector<long> f(x, 0); // Frequency array for modulo x classes
  long cnt(0);               // Current MEX candidate to check
  for (long p = 0; p < n; p++) {
    long y;
    scanf("%ld", &y);
    ++f[y % x];              // Increment frequency of residue class
    // While the count of elements in current modulo class exceeds
    // the expected count based on cnt, increment cnt
    while (f[cnt % x] > (cnt / x)) {
      ++cnt;
    }
    printf("%ld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/